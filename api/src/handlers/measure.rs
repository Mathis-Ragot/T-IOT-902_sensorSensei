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