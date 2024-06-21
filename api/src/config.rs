use std::future::Future;
use std::pin::Pin;
use actix_web::{FromRequest, HttpRequest};
use actix_web::dev::Payload;
use actix_web::web::{Data};
use config::Config;
use serde::Deserialize;
use crate::exceptions::api_exception::ApiException;
use crate::state::AppState;

/// AppConfig structure is used to represent the configuration of the application load in the environment variable at the startup of the app
/// The structure is used to store the configuration of the influxdb connection and the sensor info
/// Required: INFLUX_DB_HOST, INFLUX_DB_PORT, INFLUX_DB_NAME, INFLUX_DB_TOKEN, API_PORT, SENSOR_ID and DEVICE_NODE

#[derive(Clone, Debug, Deserialize)]
pub struct AppConfig {
    pub influx_db_host: String,
    pub influx_db_port: String,
    pub influx_db_name: String,
    pub influx_db_token: String,
    pub api_port: u16,
    pub sensor_id: u64,
    pub device_node: String,
    pub sensor_community_url: String,
}

/// Implementation of the AppConfig structure
impl AppConfig {
    /// Create a new instance of the AppConfig structure and load by default the config
    pub fn new() -> Option<Self> {
        AppConfig::load_config()
    }

    /// Load the configuration from the environment variables
    pub fn load_config() -> Option<Self> {
        Config::builder()
            .add_source(config::Environment::default())
            .build().unwrap().try_deserialize::<AppConfig>().ok()
    }
}

/// Implementation of the FromRequest trait for the AppConfig structure used for an actix handler
impl FromRequest for AppConfig {
    /// The error type for the future
    type Error = ApiException;
    /// The future response value
    type Future = Pin<Box<dyn Future<Output = Result<Self, Self::Error>>>>;

    /// Extracts the request payload and transforms it into a AppConfig structure
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
            env::set_var("INFLUX_DB_HOST", "localhost");
            env::set_var("INFLUX_DB_PORT", "8086");
            env::set_var("INFLUX_DB_NAME", "test");
            env::set_var("INFLUX_DB_TOKEN", "test");
            env::set_var("API_PORT", "8080");
            env::set_var("SENSOR_ID", "1");
            env::set_var("DEVICE_NODE", "test");
            env::set_var("SENSOR_COMMUNITY_URL", "http://localhost:8086");
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