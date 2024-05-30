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

#[cfg(test)]
mod test {
    use std::env;
    use std::sync::Once;
    use actix_web::test;
    use super::*;

    static INIT: Once = Once::new();

    pub fn initialize() {
        INIT.call_once(|| {
            env::set_var("INFLUX_URL", "http://localhost:8086");
            env::set_var("INFLUX_DB_NAME", "test");
            env::set_var("INFLUX_DB_TOKEN", "test");
            env::set_var("SENSOR_ID", "1");
            env::set_var("DEVICE_NODE", "test");
        });
    }

    #[test]
    async fn test_app_config() {
        initialize();
        let config = AppConfig::new();
        assert!(config.is_some());
    }
    
    #[test]
    async fn test_app_config_load() {
        initialize();
        let config = AppConfig::load_config();
        assert!(config.is_some());
    }
    
    #[test]
    async fn test_app_config_from_request_error() {
        initialize();
        let req = actix_web::test::TestRequest::default().to_http_request();
        let resp = AppConfig::from_request(&req, &mut actix_web::dev::Payload::None).await;
        assert!(resp.is_err());
    }
    
    #[test]
    async fn test_app_config_from_request_error_data() {
        initialize();
        let req = actix_web::test::TestRequest::default().to_http_request();
        let resp = AppConfig::from_request(&req, &mut actix_web::dev::Payload::None).await;
        assert!(resp.is_err());
    }
}