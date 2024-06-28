use std::fmt::{Debug, Display, Formatter};
use actix_web::{HttpResponse, ResponseError};
use actix_web::body::BoxBody;
use log::{error};
use serde::Serialize;
use serde_json::json;
use validator::ValidationErrors;

/// ApiException structure is used to represent the exception throw by the API
#[derive(Debug, Clone, Serialize)]
pub enum ApiException {
    /// ApiException for a bad request (400)
    BaqRequest(String),
    /// ApiException for an internal server error (500)
    Internal(String)
}

/// Implementation of the ApiException structure
impl Display for ApiException {
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        match self {
            ApiException::BaqRequest(x) => write!(f, "Bad request: {}", x),
            ApiException::Internal(x) => write!(f, "Internal error: {}", x)
        }
    }
}

/// Implementation of the ResponseError trait for the ApiException structure
impl ResponseError for ApiException {
    /// Return the error response with a basic json message
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

/// Implementation of the From trait for the ValidationErrors structure
impl From<ValidationErrors> for ApiException {
    fn from(_errors: ValidationErrors) -> Self {
        ApiException::BaqRequest("Invalid request".to_string())
    }
}

impl From<anyhow::Error> for ApiException {
    fn from(_error: anyhow::Error) -> Self {
        error!("{:?}", _error);
        ApiException::Internal("Internal error".to_string())
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
    
    #[test]
    async fn test_api_exception_from() {
        let err = ValidationErrors::new();
        let api_err = ApiException::from(err);
        assert_eq!(api_err.to_string(), ApiException::BaqRequest("Invalid request".to_string()).to_string());
    }
}