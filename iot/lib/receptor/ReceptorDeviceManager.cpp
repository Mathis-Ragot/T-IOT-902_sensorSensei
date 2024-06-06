//
// Created by clement.mathe on 06/06/2024.
//

#include "ReceptorDeviceManager.h"
#include "HttpClient.h"
#include "infrastructure/wifi/ArduinoWifiClient.h"

ReceptorDeviceManager::ReceptorDeviceManager(LoRaClass &loraInstance) :
        deviceInfo(DeviceInfos(RECEPTOR_ID, RECEPTOR_TYPE, RECEPTOR_LOCATION, RECEPTOR_LATITUDE, RECEPTOR_LONGITUDE)),
        communicationManager(new LoraReceptorManager(loraInstance)) {
    api = new SensorApi(std::make_shared<HttpClient>(), SENSOR_API_ENDPOINT);
    wifiManager = new WifiManager(new ArduinoWifiClient());
}

void ReceptorDeviceManager::init() const {
    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/, false, LORA_FREQUENCY);
    communicationManager->init();
    if (auto wifi_error = wifiManager->initialize()) {
        throw std::runtime_error(wifi_error.value().c_str());
    }
}

void ReceptorDeviceManager::loop() const {
    communicationManager->receive();
}

void ReceptorDeviceManager::communicateMeasures() {

}

void ReceptorDeviceManager::communicateInfos() {

}

ReceptorDeviceManager::~ReceptorDeviceManager() {
    delete wifiManager;
    delete api;
}


