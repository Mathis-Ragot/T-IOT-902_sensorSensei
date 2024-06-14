use reqwest;
use serde::{Deserialize, Serialize};
use crate::dtos::measure::{CreateMeasure};
use crate::exceptions::api_exception::ApiException;

/// SensorCommunity structure is used to represent the service of the sensor community wrapper
pub struct SensorCommunity;

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
        PushSensorData {
            sensor: sensor_id,
            sensordatavalues: vec![
                SensorData {
                    value_type: "P1".to_string(),
                    value: measure.value[0].to_string()
                },
                SensorData {
                    value_type: "P2".to_string(),
                    value: measure.value[1].to_string()
                }
            ]
        }
    }
}

/// SensorDataResponse structure is used to represent the response of the sensor data
#[derive(Debug, Clone, Deserialize)]
pub struct SensorDataResponse {
    pub _sensordata: u64,
}

/// PushSensorDataResponse structure is used to represent the response of the sensor data
#[derive(Debug, Clone, Deserialize)]
pub struct PushSensorDataResponse {
    #[serde(rename = "sensor")]
    pub _sensor: u64,
    #[serde(rename = "timestamp")]
    pub _timestamp: String,
    #[serde(rename = "sensordatavalues")]
    pub _sensordatavalues: Vec<SensorDataResponse>
}

/// Implementation of the SensorCommunity structure
impl SensorCommunity {
    
    /// Push data to the sensor community
    pub async fn push_data(base_url: &str, sensor_id: &String, data: PushSensorData) -> Result<PushSensorDataResponse, ApiException> {
        println!("Pushing data to sensor: {}", sensor_id);
        println!("Data: {:?}", data);
        let client = reqwest::Client::new();
        let a = client.post(format!("{}/v1/push-sensor-data/", base_url).as_str())
            .header("Content-Type", "application/json")
            .header("X-Sensor", sensor_id)
            .header("X-Pin", "1")
            .json(&data)
            .send()
            .await
            .unwrap();
        a.json::<PushSensorDataResponse>().await.map_err(|_| ApiException::Internal("Error while pushing data".to_string()))
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
            .with_body(r#"{"sensor": 1, "timestamp": "2021-01-01T00:00:00Z", "sensordatavalues": [{"_sensordata": 1}]}"#)
            .create();
        let data = PushSensorData::default();
        let resp = SensorCommunity::push_data(server.url().as_str(), &"1".to_string(), data).await;
        println!("{:?}", resp);
        assert_eq!(resp.is_ok(), true);
        let response = resp.expect("PushSensorData should not be null");
        assert_eq!(response._sensor, 1);
        assert_eq!(response._timestamp, "2021-01-01T00:00:00Z");
        assert_eq!(response._sensordatavalues.len(), 1);
    }

    #[actix_web::test]
    async fn test_push_data_error() {
        let mut server = mockito::Server::new_async().await;
        let _m = server.mock("POST", "/v1/push-sensor-data/")
            .with_status(500)
            .create();

        let data = PushSensorData::default();
        let resp = SensorCommunity::push_data(server.url().as_str(), &"1".to_string(), data).await;
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
        assert_eq!(data.sensordatavalues[1].value, "2");
    }
}