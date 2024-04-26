use actix_web::Responder;
use actix_web::web::{Data, Path};
use crate::config::AppConfig;
use crate::dtos::measure::{CreateMeasures, MeasureKind};
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
            match x.kind {
                MeasureKind::Dust => {
                    SensorCommunity::push_data(config.device_node.as_str(), PushSensorData::from_measure(config.sensor_id, x)).await?;
                },
                _ => {}
            }
        }
        Ok("".to_string())
    }

    pub async fn list_measure(client: Data<AppState>) -> impl Responder {
        MeasureService::list_measure(&client.influxdb).await;
        ""
    }

    pub async fn get_measure(kind: Path<MeasureKind>) -> Result<impl Responder, ApiException> {
        match kind.into_inner() {
            MeasureKind::Dust => Ok("Dust abc"),
            _ => Err(ApiException::Internal(String::from("Invalid measure kind")))
        }
    }
}