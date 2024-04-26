mod dtos;
mod extractors;
mod handlers;
mod exceptions;
mod services;
mod state;
mod config;

use actix_web::{web, App, HttpServer};
use actix_web::web::Data;

use crate::handlers::measure::MeasureHandler;
use crate::state::AppState;

const DEFAULT_HOST: &str = "0.0.0.0";
const DEFAULT_PORT: u16 = 8080;
const DEFAULT_WORKERS: usize = 8;

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    dotenv::dotenv().ok();
    let state = AppState::new();
    HttpServer::new(move || {
        println!("Starting server");
        App::new()
            .app_data(Data::new(state.clone()))
            .route("/measure/", web::post().to(MeasureHandler::create_measure))
            .route("/measure/{kind}/", web::get().to(MeasureHandler::get_measure))
            .route("/measure/", web::get().to(MeasureHandler::list_measure))
    })
        .workers(DEFAULT_WORKERS)
        .bind((DEFAULT_HOST, DEFAULT_PORT))?
        .run()
        .await
}