use actix_web::web::{Data, Path};
use log::info;
use crate::config::AppConfig;
use crate::dtos::measure::{CreateMeasures, MeasureKind, QueryResponse};
use crate::extractors::dto_extractor::Dto;
use crate::services::measure::MeasureService;
use crate::services::sensor_community::{PushMeasuresResponse, PushSensorData, PushSensorDataResponse, SensorCommunity};
use crate::app::AppState;

use crate::exceptions::api_exception::ApiException;


pub trait MeasureHandlers {
    async fn create_measure(measure: Dto<CreateMeasures>, config: AppConfig, client: Data<AppState>) -> Result<PushMeasuresResponse, ApiException>;
    async fn list_measure(client: Data<AppState>) -> Result<QueryResponse, ApiException>;
    async fn get_measure(kind: Path<MeasureKind>, client: Data<AppState>) -> Result<QueryResponse, ApiException>;
}

/// MeasureHandler structure is used to represent the handler of the measure
pub struct MeasureHandler;

/// Implementation of the MeasureHandler structure
impl MeasureHandlers for MeasureHandler {
    /// Route for creating a measure (POST /measure/)
    async fn create_measure(measure: Dto<CreateMeasures>, config: AppConfig, client: Data<AppState>) -> Result<PushMeasuresResponse, ApiException> {
        println!("measure, {:?}", measure.0);
        let mut response: Vec<PushSensorDataResponse> = vec![];
        for x in measure.0.values {
            MeasureService::create_measure(&x, &client.influxdb).await?;
            info!("Measure inserted into db");
            response.push(SensorCommunity::push_data(config.sensor_community_url.as_str(), &config.device_node, PushSensorData::from_measure(config.sensor_id, x.clone()), x.kind).await?);
            info!("Measure push to sensor community !");
        }
        Ok(PushMeasuresResponse(response))
    }

    /// Route for listing all measures (GET /measure/)
    async fn list_measure(client: Data<AppState>) -> Result<QueryResponse, ApiException> {
        Ok(MeasureService::list_measure(&client.influxdb).await?)
    }

    /// Route for listing all measures (GET /measure/{kind}/)
    async fn get_measure(kind: Path<MeasureKind>, client: Data<AppState>) -> Result<QueryResponse, ApiException> {
        Ok(MeasureService::get_measure(kind.into_inner(), &client.influxdb).await?)
    }
}

#[cfg(test)]
mod test {
    use std::env;
    use actix_web::{test};
    use crate::dtos::measure::CreateMeasure;
    use super::*;

    fn init_app_config() {
        env::set_var("INFLUX_DB_HOST", "localhost");
        env::set_var("INFLUX_DB_PORT", "8086");
        env::set_var("INFLUX_DB_NAME", "test");
        env::set_var("INFLUX_DB_TOKEN", "test");
        env::set_var("API_PORT", "8080");
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
        let client = Data::new(AppState::new().unwrap());
        let resp = MeasureHandler::create_measure(measure, config, client).await;
        assert_eq!(resp.ok().is_none(), true);
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
        let client = Data::new(AppState::new().unwrap());
        let resp = MeasureHandler::create_measure(measure, config, client).await;
        assert_eq!(resp.ok().is_none(), true);
    }
    
    #[test]
    async fn test_list_measure() {
        init_app_config();
        let client = Data::new(AppState::new().unwrap());
        let resp = MeasureHandler::list_measure(client).await;
        assert_eq!(resp.ok().is_none(), true);
    }
    
    #[test]
    async fn test_get_measure() {
        init_app_config();
        let client = Data::new(AppState::new().unwrap());
        let kind = Path::from(MeasureKind::Dust);
        let resp = MeasureHandler::get_measure(kind, client).await;
        assert_eq!(resp.ok().is_none(), true);
    }
}