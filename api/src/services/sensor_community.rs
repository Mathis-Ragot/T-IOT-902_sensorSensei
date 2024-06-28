use actix_web::body::BoxBody;
use actix_web::{HttpRequest, HttpResponse, Responder};
use reqwest;
use serde::{Deserialize, Serialize};
use crate::dtos::measure::{CreateMeasure, MeasureKind};

/// SensorCommunity structure is used to represent the service of the sensor community wrapper
pub struct SensorCommunity;

use anyhow::{Context, Result};
use log::{info, trace};
use reqwest::Client;

/// SensorData structure is used to represent the data of a sensor
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct SensorData {
    pub value_type: String,
    pub value: String
}

/// PushSensorData structure is used to represent the data to push to the sensor community
#[derive(Debug, Clone, Serialize, Deserialize, Default)]
pub struct PushSensorData {
    pub sensordatavalues: Vec<SensorData>,
    pub sensor: u64,
}

/// Implementation of the PushSensorData structure
impl PushSensorData {
    /// Create a new instance of the PushSensorData structure from a measure
    pub fn from_measure(sensor_id: u64, measure: CreateMeasure) -> Self {
        if let MeasureKind::Dust = &measure.kind {
            PushSensorData {
                sensor: sensor_id,
                sensordatavalues: vec![
                    SensorData {
                        value_type: "P1".to_string(),
                        value: measure.value[0].to_string()
                    },
                    SensorData {
                        value_type: "P2".to_string(),
                        value: measure.value[0].to_string()
                    }
                ]
            }
        } else {
            PushSensorData {
                sensor: sensor_id,
                sensordatavalues: vec![
                    SensorData {
                        value_type: match measure.kind {
                            MeasureKind::Dust => "P0".to_string(),
                            MeasureKind::Temperature => "temperature".to_string(),
                            MeasureKind::Humidity => "humidity".to_string(),
                            MeasureKind::Pressure => "pressure".to_string(),
                            MeasureKind::SoundLevel => "noise_LAeq".to_string(),
                        },
                        value: match measure.kind {
                            MeasureKind::Pressure => measure.value[0].parse::<f32>().map(|x| x * 100.0).map(|x| x.to_string()).unwrap_or_default(),
                            _ => measure.value[0].to_string()
                        }
                    }
                ]
            }
        }
    }
}

/// SensorDataResponse structure is used to represent the response of the sensor data
#[derive(Debug, Clone, Deserialize, Serialize)]
pub struct SensorDataResponse {
    pub sensordata: u64,
}

/// PushSensorDataResponse structure is used to represent the response of the sensor data
#[derive(Debug, Clone, Deserialize, Serialize)]
pub struct PushSensorDataResponse {
    #[serde(rename = "sensor")]
    pub sensor: u64,
    #[serde(rename = "timestamp")]
    pub timestamp: String,
    #[serde(rename = "sensordatavalues")]
    pub sensordatavalues: Vec<SensorDataResponse>
}

pub struct PushMeasuresResponse(pub Vec<PushSensorDataResponse>);

impl Responder for PushMeasuresResponse {
    type Body = BoxBody;

    fn respond_to(self, _req: &HttpRequest) -> HttpResponse<Self::Body> {
        HttpResponse::Ok().json(self.0)
    }
}

impl Responder for PushSensorDataResponse {
    type Body = BoxBody;

    fn respond_to(self, _req: &HttpRequest) -> HttpResponse<Self::Body> {
        HttpResponse::Ok().json(self)
    }
}

/// Implementation of the SensorCommunity structure
impl SensorCommunity {
    
    /// Push data to the sensor community
    pub async fn push_data(base_url: &str, sensor_id: &String, data: PushSensorData, kind: MeasureKind) -> Result<PushSensorDataResponse> {
        info!("Pushing data to sensor: {}", sensor_id);
        trace!("Data: {:?}", data);
        println!("{:?}", data);
        let a = Client::new().post(format!("{}/v1/push-sensor-data/", base_url).as_str())
            .header("Content-Type", "application/json")
            .header("X-Sensor", sensor_id)
            .header("X-Pin", Self::get_pin_from_kind(kind))
            .json(&data)
            .send()
            .await
            .context("Cannot send sensor community request !")?;

        let txt = a.text().await.unwrap();
        println!("{}", txt);

        serde_json::from_str(&txt).context("Cannot parse sensor community response !")
        //a.json::<PushSensorDataResponse>().await.context("Cannot parse sensor community response !")
    }


    fn get_pin_from_kind(kind: MeasureKind) -> String {
        match kind {
            MeasureKind::Dust => "1".to_string(),
            MeasureKind::Temperature => "7".to_string(),
            MeasureKind::Humidity => "7".to_string(),
            MeasureKind::Pressure => "3".to_string(),
            MeasureKind::SoundLevel => "15".to_string(),
        }
    }

}

#[cfg(test)]
mod test {
    use crate::dtos::measure::MeasureKind;
    use super::*;

    #[actix_web::test]
    async fn test_push_data() {
        let mut server = mockito::Server::new_async().await;
        let _m = server.mock("POST", "/v1/push-sensor-data/")
            .with_status(200)
            .with_header("content-type", "application/json")
            .with_body(r#"{"sensor": 1, "timestamp": "2021-01-01T00:00:00Z", "sensordatavalues": [{"sensordata": 1}]}"#)
            .create();
        let data = PushSensorData::default();
        let resp = SensorCommunity::push_data(server.url().as_str(), &"1".to_string(), data, MeasureKind::Dust).await;
        println!("{:?}", resp);
        assert_eq!(resp.is_ok(), true);
        let response = resp.expect("PushSensorData should not be null");
        assert_eq!(response.sensor, 1);
        assert_eq!(response.timestamp, "2021-01-01T00:00:00Z");
        assert_eq!(response.sensordatavalues.len(), 1);
    }

    #[actix_web::test]
    async fn test_push_data_error() {
        let mut server = mockito::Server::new_async().await;
        let _m = server.mock("POST", "/v1/push-sensor-data/")
            .with_status(500)
            .create();

        let data = PushSensorData::default();
        let resp = SensorCommunity::push_data(server.url().as_str(), &"1".to_string(), data, MeasureKind::Dust).await;
        assert_eq!(resp.is_err(), true);
    }
    
    #[actix_web::test]
    async fn test_from_measure() {
        let measure = CreateMeasure {
            value: vec!["1".to_string(), "2".to_string()],
            kind: MeasureKind::Dust
        };
        let data = PushSensorData::from_measure(1, measure);
        assert_eq!(data.sensor, 1);
        assert_eq!(data.sensordatavalues.len(), 2);
        assert_eq!(data.sensordatavalues[0].value_type, "P1");
        assert_eq!(data.sensordatavalues[0].value, "1");
        assert_eq!(data.sensordatavalues[1].value_type, "P2");
        assert_eq!(data.sensordatavalues[1].value, "1");
    }
    
    #[actix_web::test]
    async fn test_push_measures_response() {
        let response = PushMeasuresResponse(vec![]);
        let req = actix_web::test::TestRequest::default().to_http_request();
        let resp = response.respond_to(&req);
        assert_eq!(resp.status().as_u16(), 200);
    }
    
    #[actix_web::test]
    async fn test_push_sensor_data_response() {
        let response = PushSensorDataResponse {
            sensor: 1,
            timestamp: "2021-01-01T00:00:00Z".to_string(),
            sensordatavalues: vec![SensorDataResponse { sensordata: 1 }]
        };
        let req = actix_web::test::TestRequest::default().to_http_request();
        let resp = response.respond_to(&req);
        assert_eq!(resp.status().as_u16(), 200);
    }
}