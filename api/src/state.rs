use influxdb::Client;
use crate::config::AppConfig;

/// AppState structure is used to represent the state of the application
#[derive(Clone, Debug)]
pub struct AppState {
    /// Influxdb client
    pub influxdb: Client,
    /// Application configuration
    pub config: AppConfig,
}

/// Implementation of the AppState structure
impl AppState {
    /// Create a new instance of the AppState structure
    pub fn new() -> Self {
        let config = AppConfig::new().unwrap();
        Self {
            influxdb: Client::new(format!("http://influxdb:{}", config.influx_db_port.clone()), config.influx_db_name.clone()).with_token(config.influx_db_token.clone()),
            config
        }
    }
}

#[cfg(test)]
mod test {
    use std::env;
    use super::*;
    use actix_web::{FromRequest, test};
    use actix_web::web::Data;

    #[test]
    async fn test_app_state() {
        env::set_var("INFLUX_DB_PORT", "8086");
        env::set_var("INFLUX_DB_NAME", "test");
        env::set_var("INFLUX_DB_TOKEN", "test");
        env::set_var("SENSOR_ID", "1");
        env::set_var("DEVICE_NODE", "test");
        env::set_var("SENSOR_COMMUNITY_URL", "test");
        let state = AppState::new();
        assert_eq!(state.config.influx_db_port, "8086");
        assert_eq!(state.config.influx_db_name, "test");
    }
    
    #[test]
    async fn test_app_state_influxdb() {
        env::set_var("INFLUX_DB_PORT", "8086");
        env::set_var("INFLUX_DB_NAME", "test");
        env::set_var("INFLUX_DB_TOKEN", "test");
        env::set_var("SENSOR_ID", "1");
        env::set_var("DEVICE_NODE", "test");
        env::set_var("SENSOR_COMMUNITY_URL", "test");
        let state = AppState::new();
        let req = actix_web::test::TestRequest::default().app_data(Data::new(state)).to_http_request();
        let resp = AppConfig::from_request(&req, &mut actix_web::dev::Payload::None).await;
        assert!(resp.is_ok());
    }
}