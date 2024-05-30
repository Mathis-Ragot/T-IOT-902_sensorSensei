use influxdb::{InfluxDbWriteable, ReadQuery, WriteQuery};
use crate::dtos::measure::{CreateMeasure, MeasureKind, QueryResponse};
use crate::exceptions::api_exception::ApiException;

/// MeasureService structure is used to represent the service of the measure
pub struct MeasureService;

impl MeasureService {
    
    /// Create a measure and send it to Influxdb
    pub async fn create_measure(measure: &CreateMeasure, client: &influxdb::Client) -> Result<(), ApiException> {
        let request_query = Vec::from(measure.clone()).iter().map(|x| x.clone().into_query("measures")).collect::<Vec<WriteQuery>>();
        client.query(&request_query)
            .await
            .map_err(|_| ApiException::BaqRequest("API-1000800".to_string()))
            .and(Ok(()))
    }

    /// List all the measures from Influxdb
    pub async fn list_measure(client: &influxdb::Client) -> Result<QueryResponse, ApiException> {
        let measures = client.query(ReadQuery::new("SELECT * FROM measures"))
            .await
            .or(Err(ApiException::BaqRequest("API-1000500".to_string())))?;
        serde_json::from_str(measures.as_str()).map_err(|x| {
            println!("{:?}", x);
            ApiException::BaqRequest("API-1000900".to_string())
        })
    }

    /// Get a measure from Influxdb
    pub async fn get_measure(kind: MeasureKind, client: &influxdb::Client) -> Result<QueryResponse, ApiException> {
        let measures = client.query(ReadQuery::new(format!("SELECT * FROM measures WHERE kind = '{}'", kind))).await
            .or(Err(ApiException::BaqRequest("API-1000500".to_string())))?;
        println!("{}", measures);
        serde_json::from_str(measures.as_str()).map_err(|x| {
            println!("{:?}", x);
            ApiException::BaqRequest("API-1000900".to_string())
        })
    }
}