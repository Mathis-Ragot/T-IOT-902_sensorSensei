use std::future::Future;
use std::pin::Pin;
use actix_web::{FromRequest, HttpRequest};
use actix_web::dev::Payload;
use actix_web::web::Json;
use serde::de::DeserializeOwned;
use validator::{Validate};
use crate::exceptions::api_exception::ApiException;

/// Extractor structure for a validated DTO
pub struct Dto<T: DeserializeOwned + Validate>(pub T);

/// Implementation of the FromRequest trait for the Dto structure used for an actix handler
impl<T: DeserializeOwned + Validate + 'static> FromRequest for Dto<T> {
    /// The error type for the future
    type Error = ApiException;
    /// The future response value
    type Future = Pin<Box<dyn Future<Output = Result<Self, Self::Error>>>>;
    /// Extracts the request payload and validates it
    fn from_request(req: &HttpRequest, payload: &mut Payload) -> Self::Future {
        let json_extract = Json::<T>::from_request(req, payload);
        Box::pin(async move {
            let value = json_extract.await
                .map_err(|x| {
                    println!("Error: {:?}", x);
                    ApiException::BaqRequest(String::from("API-1000500"))
                })?.into_inner();
            value.validate()?;
            Ok(Dto(value))
        })
    }
}

#[cfg(test)]
mod test {
    use actix_web::{App, test};
    use actix_web::http::header::ContentType;
    use actix_web::web::{post};
    use crate::dtos::measure::{CreateMeasure};
    use super::*;

    #[test]
    async fn test_dto() {
        let mut app = test::init_service(
            App::new()
                .route("/", post().to(|_: Dto<CreateMeasure>| async { "OK" }))
        ).await;
        let req = test::TestRequest::post()
            .uri("/")
            .insert_header(ContentType::json())
            .set_payload(r#"{"value": ["1"], "kind": "dust"}"#)
            .to_request();
        let response = test::call_service(&mut app, req).await;
        assert!(response.status().is_success());
    }
    
    #[test]
    async fn test_dto_error() {
        let mut app = test::init_service(
            App::new()
                .route("/", post().to(|_: Dto<CreateMeasure>| async { "OK" }))
        ).await;
        let req = test::TestRequest::post()
            .uri("/")
            .insert_header(ContentType::json())
            .set_payload(r#"{}"#)
            .to_request();
        let response = test::call_service(&mut app, req).await;
        assert!(response.status().is_client_error());
    }
    
}