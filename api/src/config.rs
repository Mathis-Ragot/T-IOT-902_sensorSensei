use std::future::Future;
use std::pin::Pin;
use actix_web::{FromRequest, HttpRequest};
use actix_web::dev::Payload;
use actix_web::web::{Data};
use config::Config;
use serde::Deserialize;
use crate::exceptions::api_exception::ApiException;
use crate::state::AppState;

#[derive(Clone, Debug, Deserialize)]
pub struct AppConfig {
    pub influx_url: String,
    pub influx_db_name: String,
    pub influx_db_token: String,
    pub sensor_id: u64,
    pub device_node: String
}

impl AppConfig {
    pub fn new() -> Option<Self> {
        AppConfig::load_config()
    }

    pub fn load_config() -> Option<Self> {
        Config::builder()
            .add_source(config::Environment::default())
            .build().unwrap().try_deserialize::<AppConfig>().ok()
    }
}

impl FromRequest for AppConfig {
    type Error = ApiException;
    type Future = Pin<Box<dyn Future<Output = Result<Self, Self::Error>>>>;

    fn from_request(req: &HttpRequest, _payload: &mut Payload) -> Self::Future {
        let request = req.clone();
        Box::pin(async move {
            let config = request.app_data::<Data<AppState>>()
                .ok_or(ApiException::Internal(String::from("APE-100300")))?
                .config.clone();
            Ok(config)
        })
    }
}