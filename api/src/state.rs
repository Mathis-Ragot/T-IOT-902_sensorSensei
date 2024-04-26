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