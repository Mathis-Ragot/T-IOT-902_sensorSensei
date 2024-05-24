use std::fmt::{Debug, Display, Formatter};
use actix_web::{HttpResponse, ResponseError};
use actix_web::body::BoxBody;
use serde::Serialize;
use serde_json::json;
use validator::ValidationErrors;

#[derive(Debug, Clone, Serialize)]
pub enum ApiException {
    BaqRequest(String),
    Internal(String)
}

impl Display for ApiException {
    fn fmt(&self, _f: &mut Formatter<'_>) -> std::fmt::Result {
        todo!()
    }
}

impl ResponseError for ApiException {
    fn error_response(&self) -> HttpResponse<BoxBody> {
        match self {
            ApiException::BaqRequest(x) => {
                println!("Error: {}", x);
                HttpResponse::BadRequest().json(json!("Invalid request"))
            },
            _ => HttpResponse::InternalServerError().json(self)
        }
    }
}

impl From<ValidationErrors> for ApiException {
    fn from(errors: ValidationErrors) -> Self {
        errors.into()
    }
}