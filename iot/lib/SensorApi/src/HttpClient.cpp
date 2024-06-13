#ifdef ENABLE_IOT_HTTP_CLIENT
#include <HTTPClient.h>
#include "HttpClient.h"
#include "ArduinoJson.h"

using namespace std;

HttpClient::HttpClient() {
    this->_client = new HTTPClient();
}

HttpClient::~HttpClient() {
    delete this->_client;
}

void HttpClient::setURL(const char *serverEndpoint) {
    this->_client->setURL(serverEndpoint);
}

std::tuple<string, int> HttpClient::send(const char* type, const char *body, string url) {
    #ifdef SENSOR_API_DEBUG
        Serial.printf("Sending request to url: %s\n", url.c_str());
    #endif

    this->_client->begin(url.c_str());
    this->_client->addHeader("Content-Type", "application/json");
    int a = this->_client->sendRequest(type, body);
    string payload = this->_client->getString().c_str();
    JsonDocument doc;
    deserializeJson(doc, payload);
    return std::make_tuple(payload, a);
}

#endif