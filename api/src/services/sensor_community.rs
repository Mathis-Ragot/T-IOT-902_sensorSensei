use reqwest;
use serde::{Deserialize, Serialize};
use crate::dtos::measure::{CreateMeasure};
use crate::exceptions::api_exception::ApiException;

pub struct SensorCommunity;

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct SensorData {
    pub value_type: String,
    pub value: String
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct PushSensorData {
    pub sensordatavalues: Vec<SensorData>,
    pub sensor: u64,
}

impl PushSensorData {
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

#[derive(Debug, Clone, Deserialize)]
pub struct SensorDataResponse {
    pub sensordata: u64,
}

#[derive(Debug, Clone, Deserialize)]
pub struct PushSensorDataResponse {
    pub sensor: u64,
    pub timestamp: String,
    pub sensordatavalues: Vec<SensorDataResponse>
}

impl SensorCommunity {
    pub async fn push_data(sensor_id: &String, data: PushSensorData) -> Result<PushSensorDataResponse, ApiException> {
        println!("Pushing data to sensor: {}", sensor_id);
        println!("Data: {:?}", data);
        let client = reqwest::Client::new();
        let a = client.post("https://api.sensor.community/v1/push-sensor-data/")
            .header("Content-Type", "application/json")
            .header("X-Sensor", sensor_id)
            .header("X-Pin", "1")
            .json(&data)
            .send()
            .await
            .unwrap();
        let a = a.json::<PushSensorDataResponse>().await.unwrap();
        println!("{:?}", a);
        Ok(a)
    }
}