#include "SensorApi.h"
#include "HttpClient.h"
#include <Arduino.h>
#include <vector>
#include <WiFi.h>
#include <WiFiType.h>

void init_wifi() {
    WiFi.mode(WIFI_STA); //Optional
    WiFi.begin("OPPOa", "d6wf2yng");
    Serial.println("\nConnecting");
    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
}

void setup() {
    Serial.begin(115200);
    init_wifi();
    delay(2000);
    auto *client = new HttpClient();

    SensorApi sensorApi(std::shared_ptr<HttpClient>(client), "https://c483-163-5-23-29.ngrok-free.app");
    std::optional<Measure> a = createMeasure(String("10.2"), String("dust"));
    if (a.has_value()) {
        sensorApi.addMeasure(a.value());
    }
    sensorApi.addMeasure(a);
    sensorApi.send();
}

void loop() {
}
