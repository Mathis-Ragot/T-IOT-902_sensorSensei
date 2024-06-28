use influxdb::{InfluxDbWriteable, ReadQuery, WriteQuery};
use crate::dtos::measure::{CreateMeasure, MeasureKind, QueryResponse};

use anyhow::{Context, Result};
use log::info;

/// MeasureService structure is used to represent the service of the measure
pub struct MeasureService;

impl MeasureService {
    
    /// Create a measure and send it to Influxdb
    pub async fn create_measure(measure: &CreateMeasure, client: &influxdb::Client) -> Result<()> {
        let request_query = Vec::from(measure.clone()).iter().map(|x| x.clone().into_query("measures")).collect::<Vec<WriteQuery>>();
        client.query(&request_query)
            .await
            .context("Cannot execute query to insert measure !")
            .map(|_| ())
    }

    /// List all the measures from Influxdb
    pub async fn list_measure(client: &influxdb::Client) -> Result<QueryResponse> {
        let measures = client.query(ReadQuery::new("SELECT * FROM measures"))
            .await
            .context("Cannot execute query to list measures !")?;
        serde_json::from_str(measures.as_str())
            .context("Cannot parse measures !")
    }

    /// Get a measure from Influxdb
    pub async fn get_measure(kind: MeasureKind, client: &influxdb::Client) -> Result<QueryResponse> {
        let measures = client.query(ReadQuery::new(format!("SELECT * FROM measures WHERE kind = '{}'", kind))).await
            .context("Cannot execute query to get measure !")?;
        info!("Measures: {}", measures);
        serde_json::from_str(measures.as_str()).context("Cannot parse measures !")
    }
}