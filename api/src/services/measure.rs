use influxdb::{InfluxDbWriteable, ReadQuery, WriteQuery};
use crate::dtos::measure::{CreateMeasure, Measure, MeasureKind};
use crate::exceptions::api_exception::ApiException;

pub struct MeasureService;

impl MeasureService {
    
    pub async fn create_measure(measure: &CreateMeasure, client: &influxdb::Client) -> Result<Vec<Measure>, ApiException> {
        let a = Vec::from(measure.clone());
        let b = a.iter().map(|x| x.clone().into_query("measures")).collect::<Vec<WriteQuery>>();
        client.query(&b).await.or(Err(ApiException::BaqRequest("API-1000800".to_string())))?;
        println!("{:?}", b);
        Ok(a.iter().map(|x| Measure {
            value: vec![x.value.to_string()],
            kind: match x.key.as_str() {
                "Dust" => MeasureKind::Dust,
                "Humidity" => MeasureKind::Humidity,
                "Pressure" => MeasureKind::Pressure,
                "SoundLevel" => MeasureKind::SoundLevel,
                "Temperature" => MeasureKind::Temperature,
                _ => MeasureKind::Dust
            }
        }).collect())
    }

    pub async fn list_measure(client: &influxdb::Client) -> Result<Vec<Measure>, ApiException> {
        let measures = client.query(ReadQuery::new("SELECT * FROM measures")).await
            .or(Err(ApiException::BaqRequest("API-1000500".to_string())))?;
        println!("{}", measures);
        Ok(vec![
            Measure {
                value: vec!["1".to_string(), "2".to_string()],
                kind: MeasureKind::Dust
            },
            Measure {
                value: vec!["3".to_string(), "4".to_string()],
                kind: MeasureKind::Humidity
            }
        ])
    }

    pub async fn get_measure(kind: MeasureKind) -> Result<Measure, ApiException> {
        Ok(Measure {
            value: vec!["1".to_string(), "2".to_string()],
            kind
        })
    }
}