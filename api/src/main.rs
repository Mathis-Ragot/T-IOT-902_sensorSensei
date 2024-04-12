use std::ops::Add;
use actix_web::{web, App, HttpServer, Responder};
use chrono::{DateTime, Utc};

use influxdb::{Client, InfluxDbWriteable, WriteQuery};

const DEFAULT_HOST: &str = "0.0.0.0";
const DEFAULT_PORT: u16 = 8080;
const DEFAULT_WORKERS: usize = 8;

async fn index() -> impl Responder {
    "Hello world!"
}

async fn populate() -> impl Responder {
    let client = Client::new("http://localhost:8086", "test").with_token("A54PweRnLbGcAlAvJmBuYaQXAHVyZZ0mAnoia9B_X5HipAefdHJ830TW1wEPWZdY-lBuVFfnFMYFUqbYMl-UKQ==");
    client.ping().await.expect("Failed to ping InfluxDB");
    let mut weathers: Vec<WriteQuery> = vec![];
    for x in 0..1000 {
        weathers.push(Weather {
            time: Utc::now().add(chrono::Duration::seconds(x * -1)),
            temperature: rand::Rng::gen_range(&mut rand::thread_rng(), 0..50),
            humidity: rand::Rng::gen_range(&mut rand::thread_rng(), 0..100),
            test: "test".to_string()
        }.into_query("weather"));
    }
    client.query(weathers).await.expect("Failed to write data to InfluxDB");
    "Populating data"
}

#[derive(InfluxDbWriteable)]
struct Weather {
    time: DateTime<Utc>,
    temperature: i32,
    humidity: i32,
    #[influxdb(tag)]
    test: String
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    HttpServer::new(move || {
        App::new().service(
            web::scope("/app")
                .route("/index.html", web::get().to(index)),
        )
            .route("/populate", web::get().to(populate))
        
    })
        .workers(DEFAULT_WORKERS)
        .bind((DEFAULT_HOST, DEFAULT_PORT))?
        .run()
        .await
}