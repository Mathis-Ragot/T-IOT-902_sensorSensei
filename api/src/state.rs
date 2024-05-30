use influxdb::Client;
use crate::config::AppConfig;

#[derive(Clone, Debug)]
pub struct AppState {
    pub influxdb: Client,
    pub config: AppConfig,
}

impl AppState {
    pub fn new() -> Self {
        let config = AppConfig::new().unwrap();
        Self {
            influxdb: Client::new(config.influx_url.clone(), config.influx_db_name.clone()).with_token(config.influx_db_token.clone()),
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
        env::set_var("INFLUX_URL", "http://localhost:8086");
        env::set_var("INFLUX_DB_NAME", "test");
        env::set_var("INFLUX_DB_TOKEN", "test");
        env::set_var("SENSOR_ID", "1");
        env::set_var("DEVICE_NODE", "test");
        let state = AppState::new();
        assert_eq!(state.config.influx_url, "http://localhost:8086");
        assert_eq!(state.config.influx_db_name, "test");
    }
    
    #[test]
    async fn test_app_state_influxdb() {
        env::set_var("INFLUX_URL", "http://localhost:8086");
        env::set_var("INFLUX_DB_NAME", "test");
        env::set_var("INFLUX_DB_TOKEN", "test");
        env::set_var("SENSOR_ID", "1");
        env::set_var("DEVICE_NODE", "test");
        let state = AppState::new();
        let req = actix_web::test::TestRequest::default().app_data(Data::new(state)).to_http_request();
        let resp = AppConfig::from_request(&req, &mut actix_web::dev::Payload::None).await;
        assert!(resp.is_ok());
    }
}