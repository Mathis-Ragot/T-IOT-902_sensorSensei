use actix_web::web::{Data, Path};
use crate::config::AppConfig;
use crate::dtos::measure::{CreateMeasures, MeasureKind, QueryResponse};
use crate::exceptions::api_exception::ApiException;
use crate::extractors::dto_extractor::Dto;
use crate::services::measure::MeasureService;
use crate::services::sensor_community::{PushSensorData, SensorCommunity};
use crate::state::AppState;

pub struct MeasureHandler;

impl MeasureHandler {
    
    pub async fn create_measure(measure: Dto<CreateMeasures>, config: AppConfig, client: Data<AppState>) -> Result<String, ApiException> {
        for x in measure.0.values {
            MeasureService::create_measure(&x, &client.influxdb).await?;
            if let MeasureKind::Dust = x.kind {
                SensorCommunity::push_data(&config.device_node, PushSensorData::from_measure(config.sensor_id, x)).await?;
            }
        }
        Ok(String::from("OK"))
    }

    pub async fn list_measure(client: Data<AppState>) -> Result<QueryResponse, ApiException> {
        MeasureService::list_measure(&client.influxdb).await
    }

    pub async fn get_measure(kind: Path<MeasureKind>, client: Data<AppState>) -> Result<QueryResponse, ApiException> {
        MeasureService::get_measure(kind.into_inner(), &client.influxdb).await
    }
}

#[cfg(test)]
mod test {

    use actix_web::{test};
    use crate::dtos::measure::CreateMeasure;
    use super::*;
    
    #[test]
    async fn test_measure_handler() {
        let measure = Dto(CreateMeasures {
            values: vec![
                CreateMeasure {
                    value: vec!["1".to_string(), "2".to_string()],
                    kind: MeasureKind::Dust,
                }
            ],
        });
        let config = AppConfig::new().unwrap();
        let client = Data::new(AppState::new());
        let resp = MeasureHandler::create_measure(measure, config, client).await;
        assert_eq!(resp.ok(), None);
    }
    
    #[test]
    async fn test_measure_handler_error() {
        let measure = Dto(CreateMeasures {
            values: vec![
                CreateMeasure {
                    value: vec!["1".to_string(), "2".to_string()],
                    kind: MeasureKind::Dust,
                }
            ],
        });
        let config = AppConfig::new().unwrap();
        let client = Data::new(AppState::new());
        let resp = MeasureHandler::create_measure(measure, config, client).await;
        assert_eq!(resp.ok(), None);
    }
    
    #[test]
    async fn test_list_measure() {
        let client = Data::new(AppState::new());
        let resp = MeasureHandler::list_measure(client).await;
        assert_eq!(resp.ok().is_none(), true);
    }
    
    #[test]
    async fn test_get_measure() {
        let client = Data::new(AppState::new());
        let kind = Path::from(MeasureKind::Dust);
        let resp = MeasureHandler::get_measure(kind, client).await;
        assert_eq!(resp.ok().is_none(), true);
    }
}