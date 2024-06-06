#include <WiFi.h>
#include "ArduinoWifiClient.h"

bool ArduinoWifiClient::connect(std::string ssid, std::string password, int max_delay) {
    WiFiClass::mode(WIFI_STA); //Optional
    WiFi.begin(ssid.c_str(), password.c_str());
    #ifdef WIFI_DEBUG
        Serial.println("Connecting to wifi....");
    #endif
    int counter = 0;
    #pragma unroll
    while (WiFiClass::status() != WL_CONNECTED) {
        delay(WIFI_DELAY_COUNT);
        counter += WIFI_DELAY_COUNT;
        if (counter > max_delay) {
        #ifdef APP_SENSOR_DEBUG
            Serial.println("\nWifi connection timeout !");
        #endif
            return false;
        }
    }
    #ifdef WIFI_DEBUG
        Serial.printf("Connected to the WiFi network: %s\n", WiFi.localIP().toString().c_str());
    #endif
    return true;
}

bool ArduinoWifiClient::disconnect() {
    return WiFi.disconnect();
}

bool ArduinoWifiClient::restart() {
    return false;
}
