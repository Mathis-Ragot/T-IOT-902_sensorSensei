use std::fmt::Display;
use actix_web::body::BoxBody;
use actix_web::Responder;
use influxdb::InfluxDbWriteable;
use serde::{Deserialize, Serialize};
use serde_json::Value;
use validator::{Validate};

#[derive(Serialize, Deserialize, Validate, Clone)]
pub struct Measure {
    #[validate(length(min = 2, max = 2))]
    pub value: Vec<String>,
    pub kind: MeasureKind,
}

impl Responder for Measure {
    type Body = BoxBody;

    fn respond_to(self, _req: &actix_web::HttpRequest) -> actix_web::HttpResponse {
        actix_web::HttpResponse::Ok().json(self)
    }
}

#[derive(Serialize, Clone, InfluxDbWriteable)]
pub struct TimeMeasure {
    pub time: chrono::DateTime<chrono::Utc>,
    pub value: f64,
    #[influxdb(tag)]
    pub kind: String,
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
                TimeMeasure::new(value.value[0].parse::<f64>().unwrap(), "dust".to_string(), "P1".to_string()),
                TimeMeasure::new(value.value[1].parse::<f64>().unwrap(), "dust".to_string(), "P2".to_string())
            ],
            MeasureKind::Humidity => vec![
                TimeMeasure::new(value.value[0].parse::<f64>().unwrap(), "humidity".to_string(), "P1".to_string()),
            ],
            MeasureKind::Pressure => vec![
                TimeMeasure::new(value.value[0].parse::<f64>().unwrap(), "pressure".to_string(), "P1".to_string()),
            ],
            MeasureKind::SoundLevel => vec![
                TimeMeasure::new(value.value[0].parse::<f64>().unwrap(), "sound_level".to_string(), "P1".to_string()),
            ],
            MeasureKind::Temperature => vec![
                TimeMeasure::new(value.value[0].parse::<f64>().unwrap(), "temperature".to_string(), "P1".to_string()),
            ]
        }
    }
}

impl From<CreateMeasure> for TimeMeasure {
    fn from(measure: CreateMeasure) -> Self {
        TimeMeasure {
            time: chrono::Utc::now(),
            value: measure.value[0].parse::<f64>().unwrap(),
            kind: measure.kind.to_string(),
            value_type: "P1".to_string()
        }
    }
}

impl TimeMeasure {
    pub fn new(value: f64, kind: String, value_type: String) -> Self {
        TimeMeasure {
            time: chrono::Utc::now(),
            value,
            kind,
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
    #[serde(rename = "dust")]
    Dust,
    #[serde(rename = "temperature")]
    Temperature,
    #[serde(rename = "humidity")]
    Humidity,
    #[serde(rename = "pressure")]
    Pressure,
    #[serde(rename = "sound_level")]
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

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct QueryResponse {
    pub results: Vec<QueryResult>,
}

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct QueryResult {
    pub statement_id: u64,
    pub series: Vec<SeriesResult>,
}

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct SeriesResult {
    pub name: String,
    pub columns: Vec<String>,
    pub values: Vec<Vec<Value>>,
}

impl Responder for QueryResponse {
    type Body = BoxBody;

    fn respond_to(self, _req: &actix_web::HttpRequest) -> actix_web::HttpResponse {
        actix_web::HttpResponse::Ok().json(self)
    }
}