use std::fmt::Display;
use influxdb::InfluxDbWriteable;
use serde::{Deserialize, Serialize};
use validator::{Validate};

#[derive(Serialize, Validate, Clone)]
pub struct Measure {
    #[validate(length(min = 2, max = 2))]
    pub value: Vec<String>,
    pub kind: MeasureKind,
}

#[derive(Serialize, Clone, InfluxDbWriteable)]
pub struct TimeMeasure {
    pub time: chrono::DateTime<chrono::Utc>,
    pub value: f64,
    #[influxdb(tag)]
    pub key: String,
    #[influxdb(tag)]
    pub value_type: String,
}

#[derive(Deserialize, Validate, Clone, Serialize)]
pub struct CreateMeasure {
    #[validate(length(min = 1, max = 255))]
    pub value: Vec<String>,
    pub kind: MeasureKind,
}

impl From<CreateMeasure> for Vec<TimeMeasure> {
    fn from(value: CreateMeasure) -> Self {
        match &value.kind {
            MeasureKind::Dust => vec![
                TimeMeasure::new(value.value[0].parse::<f64>().unwrap(), "Dust".to_string(), "P1".to_string()),
                TimeMeasure::new(value.value[1].parse::<f64>().unwrap(), "Dust".to_string(), "P2".to_string())
            ],
            MeasureKind::Humidity => vec![
                TimeMeasure::new(value.value[0].parse::<f64>().unwrap(), "Humidity".to_string(), "P1".to_string()),
            ],
            MeasureKind::Pressure => vec![
                TimeMeasure::new(value.value[0].parse::<f64>().unwrap(), "Pressure".to_string(), "P1".to_string()),
            ],
            MeasureKind::SoundLevel => vec![
                TimeMeasure::new(value.value[0].parse::<f64>().unwrap(), "SoundLevel".to_string(), "P1".to_string()),
            ],
            MeasureKind::Temperature => vec![
                TimeMeasure::new(value.value[0].parse::<f64>().unwrap(), "Temperature".to_string(), "P1".to_string()),
            ]
        }
    }
}

impl From<CreateMeasure> for TimeMeasure {
    fn from(measure: CreateMeasure) -> Self {
        TimeMeasure {
            time: chrono::Utc::now(),
            value: measure.value[0].parse::<f64>().unwrap(),
            key: measure.kind.to_string(),
            value_type: "P1".to_string()
        }
    }
}

impl TimeMeasure {
    pub fn new(value: f64, key: String, value_type: String) -> Self {
        TimeMeasure {
            time: chrono::Utc::now(),
            value,
            key,
            value_type
        }
    }
}

/// CreateMeasures DTO is used to create multiple measures at once
/// Handle by the /measure/ routes
#[derive(Deserialize, Validate, Clone)]
pub struct CreateMeasures {
    pub values: Vec<CreateMeasure>,
}

#[derive(Serialize, Deserialize, Clone)]
pub enum MeasureKind {
    Dust,
    Temperature,
    Humidity,
    Pressure,
    SoundLevel,
}

impl Display for MeasureKind {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            MeasureKind::Dust => write!(f, "dust"),
            MeasureKind::Temperature => write!(f, "temperature"),
            MeasureKind::Humidity => write!(f, "humidity"),
            MeasureKind::Pressure => write!(f, "pressure"),
            MeasureKind::SoundLevel => write!(f, "sound_level"),
        }
    }
}