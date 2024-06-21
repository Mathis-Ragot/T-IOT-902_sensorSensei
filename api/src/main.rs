mod dtos;
mod extractors;
mod handlers;
mod exceptions;
mod services;
mod app;
mod config;

use crate::app::App;

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    let app: App = App::new().map_err(|e| {
        eprintln!("Error while starting the application: {:?}", e);
        std::process::exit(1);
    }).unwrap();
    app.start().await
}