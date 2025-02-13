use std::fmt::Display;
use actix_web::body::BoxBody;
use actix_web::{HttpResponse, Responder};
use influxdb::InfluxDbWriteable;
use serde::{Deserialize, Serialize};
use serde_json::Value;
use validator::{Validate};

/// Measure DTO is used to represent a measure
#[derive(Serialize, Deserialize, Validate, Clone, Default)]
pub struct Measure {
    #[validate(length(min = 2, max = 2))]
    pub value: Vec<String>,
    pub kind: MeasureKind,
}

/// Implementation of the Responder trait for the Measure structure
impl Responder for Measure {
    type Body = BoxBody;
    /// Respond to the request with the json of Measure
    fn respond_to(self, _req: &actix_web::HttpRequest) -> HttpResponse {
        HttpResponse::Ok().json(self)
    }
}

/// TimeMeasure DTO is used to represent a measure with a timestamp (used for influxdb)
#[derive(Serialize, Clone, InfluxDbWriteable, Default)]
pub struct TimeMeasure {
    pub time: chrono::DateTime<chrono::Utc>,
    pub value: f64,
    #[influxdb(tag)]
    pub kind: String,
    #[influxdb(tag)]
    pub value_type: String,
}

/// Implementation of the Responder trait for the TimeMeasure structure
#[derive(Debug, Deserialize, Validate, Clone, Serialize, Default)]
pub struct CreateMeasure {
    #[validate(length(min = 1, max = 255))]
    pub value: Vec<String>,
    pub kind: MeasureKind,
}

/// Implementation of the Responder trait for the CreateMeasure structure
impl From<CreateMeasure> for Vec<TimeMeasure> {
    /// Convert a CreateMeasure to a TimeMeasure
    fn from(value: CreateMeasure) -> Self {
        match &value.kind {
            MeasureKind::Dust => vec![
                TimeMeasure::new(value.value[0].parse::<f64>().unwrap(), "dust".to_string(), "P1".to_string()),
            ],
            MeasureKind::Humidity => vec![
                TimeMeasure::new(value.value[0].parse::<f64>().unwrap(), "humidity".to_string(), "%".to_string()),
            ],
            MeasureKind::Pressure => vec![
                TimeMeasure::new(value.value[0].parse::<f64>().unwrap(), "pressure".to_string(), "hPa".to_string()),
            ],
            MeasureKind::SoundLevel => vec![
                TimeMeasure::new(value.value[0].parse::<f64>().unwrap(), "sound_level".to_string(), "dB".to_string()),
            ],
            MeasureKind::Temperature => vec![
                TimeMeasure::new(value.value[0].parse::<f64>().unwrap(), "temperature".to_string(), "celsius".to_string()),
            ]
        }
    }
}

/// Implementation of the Responder trait for the CreateMeasure structure
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

/// Implementation of the Responder trait for the CreateMeasure structure
impl TimeMeasure {
    /// Create a new TimeMeasure
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
#[derive(Debug, Deserialize, Validate, Clone, Default)]
pub struct CreateMeasures {
    pub values: Vec<CreateMeasure>,
}

/// Available type of measures
#[derive(Serialize, Deserialize, Clone, Debug, PartialEq, Default)]
pub enum MeasureKind {
    /// json value 'dust'
    #[default]
    #[serde(rename = "dust")]
    Dust,
    /// json value 'temperature'
    #[serde(rename = "temperature")]
    Temperature,
    /// json value 'humidity'
    #[serde(rename = "humidity")]
    Humidity,
    /// json value 'pressure'
    #[serde(rename = "pressure")]
    Pressure,
    /// json value 'sound_level'
    #[serde(rename = "sound_level")]
    SoundLevel,
}

/// Implementation of the Display trait for the MeasureKind structure
impl Display for MeasureKind {
    /// Display the MeasureKind
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

/// Query DTO is used to represent a query returned by 'influxdb write query'
#[derive(Serialize, Deserialize, Debug, Clone, Default)]
pub struct QueryResponse {
    pub results: Vec<QueryResult>,
}

/// sub-structure of QueryResponse
#[derive(Serialize, Deserialize, Debug, Clone, Default)]
pub struct QueryResult {
    pub statement_id: u64,
    pub series: Vec<SeriesResult>,
}

/// sub-structure of QueryResult containing the values of influxdb query
#[derive(Serialize, Deserialize, Debug, Clone, Default)]
pub struct SeriesResult {
    pub name: String,
    pub columns: Vec<String>,
    pub values: Vec<Vec<Value>>,
}

/// Implementation of the Responder trait for the QueryResponse structure
impl Responder for QueryResponse {
    type Body = BoxBody;

    /// Respond to the request with the json of QueryResponse
    fn respond_to(self, _req: &actix_web::HttpRequest) -> actix_web::HttpResponse {
        HttpResponse::Ok().json(self)
    }
}

#[cfg(test)]
mod tests {
    use actix_web::test;
    use super::*;

    #[test]
    async fn basic_measure() {
        let measure = Measure {
            value: vec!["1".to_string(), "2".to_string()],
            kind: MeasureKind::Dust,
        };
        assert_eq!(measure.value, vec!["1".to_string(), "2".to_string()]);
        assert_eq!(measure.kind, MeasureKind::Dust);
    }

    #[test]
    async fn basic_time_measure() {
        let time_measure = TimeMeasure {
            time: chrono::Utc::now(),
            value: 1.0,
            kind: "dust".to_string(),
            value_type: "P1".to_string(),
        };
        assert_eq!(time_measure.value, 1.0);
        assert_eq!(time_measure.kind, "dust".to_string());
        assert_eq!(time_measure.value_type, "P1".to_string());
    }

    #[test]
    async fn basic_create_measure() {
        let create_measure = CreateMeasure {
            value: vec!["1".to_string()],
            kind: MeasureKind::Dust,
        };
        assert_eq!(create_measure.value, vec!["1".to_string()]);
        assert_eq!(create_measure.kind, MeasureKind::Dust);
    }

    #[test]
    async fn basic_create_measures() {
        let create_measures = CreateMeasures {
            values: vec![
                CreateMeasure {
                    value: vec!["1".to_string()],
                    kind: MeasureKind::Dust,
                }
            ],
        };
        assert_eq!(create_measures.values.len(), 1);
    }

    #[test]
    async fn basic_measure_kind() {
        let measure_kind = MeasureKind::Dust;
        assert_eq!(measure_kind.to_string(), "dust");
    }

    #[test]
    async fn basic_query_response() {
        let query_response = QueryResponse {
            results: vec![
                QueryResult {
                    statement_id: 0,
                    series: vec![
                        SeriesResult {
                            name: "test".to_string(),
                            columns: vec!["test".to_string()],
                            values: vec![vec![Value::String("test".to_string())]],
                        }
                    ],
                }
            ],
        };
        assert_eq!(query_response.results.len(), 1);
    }

    #[test]
    async fn basic_series_result() {
        let series_result = SeriesResult {
            name: "test".to_string(),
            columns: vec!["test".to_string()],
            values: vec![vec![Value::String("test".to_string())]],
        };
        assert_eq!(series_result.name, "test".to_string());
    }

    #[test]
    async fn basic_query_result() {
        let query_result = QueryResult::default();
        assert_eq!(query_result.statement_id, 0);
    }

    #[test]
    async fn basic_time_measure_from_create_measure() {
        let create_measure = CreateMeasure {
            value: vec!["1".to_string()],
            kind: MeasureKind::Dust,
        };
        let time_measure: TimeMeasure = create_measure.into();
        assert_eq!(time_measure.value, 1.0);

        let mut a = CreateMeasure::default();
        a.value = vec!["1".to_string()];
        a.kind = MeasureKind::Humidity;
        let time_measure: TimeMeasure = a.clone().into();
        assert_eq!(time_measure.kind, "humidity".to_string());

        a.kind = MeasureKind::Pressure;
        let time_measure: TimeMeasure = a.clone().into();
        assert_eq!(time_measure.kind, "pressure".to_string());

        a.kind = MeasureKind::SoundLevel;
        let time_measure: TimeMeasure = a.clone().into();
        assert_eq!(time_measure.kind, "sound_level".to_string());

        a.kind = MeasureKind::Temperature;
        let time_measure: TimeMeasure = a.clone().into();
        assert_eq!(time_measure.kind, "temperature".to_string());
    }

    #[test]
    async fn basic_vec_time_measure_from_create_measure() {
        let mut create_measure = CreateMeasure {
            value: vec!["1".to_string(), "2".to_string()],
            kind: MeasureKind::Dust,
        };
        let time_measures: Vec<TimeMeasure> = create_measure.clone().into();
        assert_eq!(time_measures.len(), 1);
        create_measure.kind = MeasureKind::Humidity;
        let time_measures: Vec<TimeMeasure> = create_measure.clone().into();
        assert_eq!(time_measures.len(), 1);
        create_measure.kind = MeasureKind::Pressure;
        let time_measures: Vec<TimeMeasure> = create_measure.clone().into();
        assert_eq!(time_measures.len(), 1);
        create_measure.kind = MeasureKind::SoundLevel;
        let time_measures: Vec<TimeMeasure> = create_measure.clone().into();
        assert_eq!(time_measures.len(), 1);
        create_measure.kind = MeasureKind::Temperature;
        let time_measures: Vec<TimeMeasure> = create_measure.clone().into();
        assert_eq!(time_measures.len(), 1);
    }

    #[test]
    async fn basic_time_measure_new() {
        let time_measure = TimeMeasure::new(1.0, "dust".to_string(), "P1".to_string());
        assert_eq!(time_measure.value, 1.0);
    }

    #[test]
    async fn basic_measure_kind_display() {
        let mut measure_kind = MeasureKind::Dust;
        assert_eq!(measure_kind.to_string(), "dust");
        measure_kind = MeasureKind::Temperature;
        assert_eq!(measure_kind.to_string(), "temperature");
        measure_kind = MeasureKind::Dust;
        assert_eq!(measure_kind.to_string(), "dust");
        measure_kind = MeasureKind::Humidity;
        assert_eq!(measure_kind.to_string(), "humidity");
        measure_kind = MeasureKind::Pressure;
        assert_eq!(measure_kind.to_string(), "pressure");
        measure_kind = MeasureKind::SoundLevel;
        assert_eq!(measure_kind.to_string(), "sound_level");
    }

    #[test]
    async fn basic_query_response_responder() {
        let query_response = QueryResponse::default();
        let response = query_response.respond_to(&test::TestRequest::default().to_http_request());
        assert_eq!(response.status(), actix_web::http::StatusCode::OK);
    }

    #[test]
    async fn basic_measure_responder() {
        let measure = Measure::default();
        let response = measure.respond_to(&test::TestRequest::default().to_http_request());
        assert_eq!(response.status(), actix_web::http::StatusCode::OK);
    }
}