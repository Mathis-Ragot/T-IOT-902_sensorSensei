//
// Created by clement.mathe on 06/06/2024.
//

#include "ReceptorApp.h"
#include "infrastructure/wifi/ArduinoWifiClient.h"
#include "HttpClient.h"

ReceptorApp::ReceptorApp() {
    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/, true, LORA_FREQUENCY);
    wifiManager = new WifiManager(new ArduinoWifiClient());
    if (auto wifi_error = wifiManager->initialize()) {
        throw std::runtime_error(wifi_error.value().c_str());
    }
    deviceManager = new ReceptorDeviceManager(loraInstance);
    deviceManager->init();

    api = new SensorApi(std::make_shared<HttpClient>(), SENSOR_API_ENDPOINT);
}

ReceptorApp::~ReceptorApp() {
    delete deviceManager;
    delete wifiManager;
    delete api;
}

void ReceptorApp::loop() {
    deviceManager->loop();
}