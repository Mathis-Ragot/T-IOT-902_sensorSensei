use actix_web::{HttpServer, web};
use actix_web::middleware::Logger;
use actix_web::web::Data;
use anyhow::Context;
use env_logger::{Env, init_from_env};
use influxdb::Client;
use crate::config::AppConfig;
use crate::handlers::measure::{MeasureHandler, MeasureHandlers};
use anyhow::Result;
use tracing::info;

pub struct App {
    pub state: AppState,
    pub workers: usize,
    pub host: String,
    pub port: u16,
}

impl App {
    pub fn new() -> Result<Self> {
        dotenv::dotenv().context("Error while loading/reading the .env file !")?;
        init_from_env(Env::new().default_filter_or("info"));
        Ok(Self {
            state: AppState::new()?,
            workers: 8,
            host: String::from("0.0.0.0"),
            port: 8080 
        })
    }

    pub async fn start(&self) -> std::io::Result<()> {
        let data = Data::new(self.state.clone());
        info!("Starting server at at: http://{}:{}", self.host, self.port);
        HttpServer::new(move || {
            actix_web::App::new()
                .app_data(data.clone())
                .wrap(Logger::default())
                .route("/measure/", web::post().to(MeasureHandler::create_measure))
                .route("/measure/{kind}/", web::get().to(MeasureHandler::get_measure))
                .route("/measure/", web::get().to(MeasureHandler::list_measure))
        })
            .workers(self.workers)
            .bind((self.host.as_str(), self.port))?
            .run()
            .await
    }

}

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
    pub fn new() -> Result<Self> {
        let config = AppConfig::new()?;
        Ok(Self {
            influxdb: Client::new(config.influx_url.clone(), config.influx_db_name.clone()).with_token(config.influx_db_token.clone()),
            config
        })
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
        env::set_var("SENSOR_COMMUNITY_URL", "test");
        let state = AppState::new().unwrap();
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
        env::set_var("SENSOR_COMMUNITY_URL", "test");
        let state = AppState::new();
        let req = actix_web::test::TestRequest::default().app_data(Data::new(state)).to_http_request();
        let resp = AppConfig::from_request(&req, &mut actix_web::dev::Payload::None).await;
        assert!(resp.is_ok());
    }
}