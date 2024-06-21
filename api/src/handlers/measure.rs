use actix_web::web::{Data, Path};
use crate::config::AppConfig;
use crate::dtos::measure::{CreateMeasures, MeasureKind, QueryResponse};
use crate::exceptions::api_exception::ApiException;
use crate::extractors::dto_extractor::Dto;
use crate::services::measure::MeasureService;
use crate::services::sensor_community::{PushSensorData, SensorCommunity};
use crate::state::AppState;

/// MeasureHandler structure is used to represent the handler of the measure
pub struct MeasureHandler;

/// Implementation of the MeasureHandler structure
impl MeasureHandler {
    /// Route for creating a measure (POST /measure/)
    pub async fn create_measure(measure: Dto<CreateMeasures>, config: AppConfig, client: Data<AppState>) -> Result<String, ApiException> {
        for x in measure.0.values {
            MeasureService::create_measure(&x, &client.influxdb).await?;
            if let MeasureKind::Dust = x.kind {
                SensorCommunity::push_data(config.sensor_community_url.as_str(), &config.device_node, PushSensorData::from_measure(config.sensor_id, x)).await?;
            }
        }
        Ok(String::from("OK"))
    }

    /// Route for listing all measures (GET /measure/)
    pub async fn list_measure(client: Data<AppState>) -> Result<QueryResponse, ApiException> {
        MeasureService::list_measure(&client.influxdb).await
    }

    /// Route for listing all measures (GET /measure/{kind}/)
    pub async fn get_measure(kind: Path<MeasureKind>, client: Data<AppState>) -> Result<QueryResponse, ApiException> {
        MeasureService::get_measure(kind.into_inner(), &client.influxdb).await
    }
}

#[cfg(test)]
mod test {
    use std::env;
    use actix_web::{test};
    use crate::dtos::measure::CreateMeasure;
    use super::*;

    fn init_app_config() {
        env::set_var("INFLUX_DB_PORT", "8086");
        env::set_var("INFLUX_DB_NAME", "test");
        env::set_var("INFLUX_DB_TOKEN", "test");
        env::set_var("SENSOR_ID", "1");
        env::set_var("DEVICE_NODE", "test");
        env::set_var("SENSOR_COMMUNITY_URL", "http://localhost:8087");
    }
    
    #[test]
    async fn test_measure_handler() {
        init_app_config();
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
        init_app_config();
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
        init_app_config();
        let client = Data::new(AppState::new());
        let resp = MeasureHandler::list_measure(client).await;
        assert_eq!(resp.ok().is_none(), true);
    }
    
    #[test]
    async fn test_get_measure() {
        init_app_config();
        let client = Data::new(AppState::new());
        let kind = Path::from(MeasureKind::Dust);
        let resp = MeasureHandler::get_measure(kind, client).await;
        assert_eq!(resp.ok().is_none(), true);
    }
}