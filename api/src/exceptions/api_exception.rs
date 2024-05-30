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
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        match self {
            ApiException::BaqRequest(x) => write!(f, "Bad request: {}", x),
            ApiException::Internal(x) => write!(f, "Internal error: {}", x)
        }
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

#[cfg(test)]
mod test {
    use actix_web::test;
    use super::*;

    #[test]
    async fn test_api_exception() {
        let err = ApiException::BaqRequest("Invalid request".to_string());
        let resp = err.error_response();
        assert_eq!(resp.status(), 400);
    }

    #[test]
    async fn test_api_exception_internal() {
        let err = ApiException::Internal("Internal error".to_string());
        let resp = err.error_response();
        assert_eq!(resp.status(), 500);
    }
    
    #[test]
    async fn test_api_exception_display() {
        let err = ApiException::BaqRequest("Invalid request".to_string());
        assert_eq!(err.to_string(), "Bad request: Invalid request");
    }

    #[test]
    async fn test_api_exception_display_internal() {
        let err = ApiException::Internal("Internal error".to_string());
        assert_eq!(err.to_string(), "Internal error: Internal error");
    }
}