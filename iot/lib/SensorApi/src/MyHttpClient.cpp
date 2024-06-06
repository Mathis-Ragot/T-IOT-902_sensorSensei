#include <MyHttpClient.h>
#include "ArduinoJson.h"

MyHttpClient::MyHttpClient() {
    this->_client = new HTTPClient();
}

MyHttpClient::~MyHttpClient() {
    delete this->_client;
}

void MyHttpClient::setURL(const char *serverEndpoint) {
    this->_client->setURL(serverEndpoint);
}

std::tuple<String, int> MyHttpClient::send(const char* type, const char *body, String url) {
    #ifdef SENSOR_API_DEBUG
        Serial.printf("Sending request to url: %s\n", url.c_str());
    #endif

    this->_client->begin(url);
    this->_client->addHeader("Content-Type", "application/json");
    int a = this->_client->sendRequest(type, body);
    String payload = this->_client->getString();
    JsonDocument doc;
    deserializeJson(doc, payload);
    return std::make_tuple(payload, a);
}