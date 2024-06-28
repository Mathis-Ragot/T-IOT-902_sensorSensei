#ifdef ENABLE_IOT_HTTP_CLIENT
#include <HTTPClient.h>
#include "MyHttpClient.h"
#include "ArduinoJson.h"

using namespace std;

MyHttpClient::MyHttpClient() {
    this->_client = new HTTPClient();
}

MyHttpClient::~MyHttpClient() {
    delete this->_client;
}

void MyHttpClient::setURL(const char *serverEndpoint) {
    this->_client->setURL(serverEndpoint);
}

std::tuple<string, int> MyHttpClient::send(const char* type, const char *body, string url) {
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