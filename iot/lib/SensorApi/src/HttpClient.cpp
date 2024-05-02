
#include <HTTPClient.h>
#include "HttpClient.h"
#include "ArduinoJson.h"

HttpClient::HttpClient() {
    this->_client = new HTTPClient();
}

HttpClient::~HttpClient() {
    delete this->_client;
}

void HttpClient::setURL(const char *serverEndpoint) {
    this->_client->setURL(serverEndpoint);
}

const char *HttpClient::send(const char *url) {
    printf("Sending request\n");
    this->_client->begin(url);
    this->_client->addHeader("Content-Type", "application/json");
    int a = this->_client->POST(R"({"values": [{"value": ["13.2", "15.20"], "kind": "Dust"}]})");
    printf("Response: %d\n", a);
    String payload = this->_client->getString();
    JsonDocument doc;
    deserializeJson(doc, payload);
    printf("Body: %s\n", payload.c_str());
    return "Success";
}