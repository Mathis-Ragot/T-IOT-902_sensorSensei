//
// Created by clement.mathe on 06/06/2024.
//

#include "ReceptorDeviceManager.h"
#include "MyHttpClient.h"
#include "infrastructure/wifi/ArduinoWifiClient.h"

ReceptorDeviceManager::ReceptorDeviceManager(LoRaClass &loraInstance) :
        queueManager(20),
        deviceInfo(DeviceInfos(RECEPTOR_ID, RECEPTOR_TYPE, RECEPTOR_LOCATION, RECEPTOR_LATITUDE, RECEPTOR_LONGITUDE)) {


    communicationManager = new LoraReceptorManager(loraInstance, queueManager);
    api = new SensorApi(std::make_shared<MyHttpClient>(), SENSOR_API_ENDPOINT);
    wifiManager = new WifiManager(new ArduinoWifiClient());
}

void ReceptorDeviceManager::init() const {
    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/, false, LORA_FREQUENCY);
    Heltec.display->init();
    Heltec.display->clear();
    Heltec.display->display();

    communicationManager->init();
    communicationManager->connect();

    if (auto wifi_error = wifiManager->initialize()) {
        Serial.println(wifi_error.value().c_str());
    }
}


void ReceptorDeviceManager::loop() {
    std::vector<uint8_t> receivedPacket;
    if (queueManager.dequeuePacket(receivedPacket)) {
        Serial.print("Processing received packet at: ");
        Serial.println(millis());
        processReceivedPacket(receivedPacket);
    }
}

void ReceptorDeviceManager::processReceivedPacket(std::vector<uint8_t> &packet) {
    Serial.print("Received packet: ");
    Heltec.display->clear();
    String displayData = "Received: ";

    for (const auto& byte : packet) {
        Serial.print(byte, HEX);
        Serial.print(" ");
        displayData += String(byte, HEX) + " ";
    }
    Serial.println();

    Heltec.display->drawString(0, 0, displayData);
    Heltec.display->display();
}

void ReceptorDeviceManager::communicateMeasures() {

}

void ReceptorDeviceManager::communicateInfos() {

}

ReceptorDeviceManager::~ReceptorDeviceManager() {
    delete wifiManager;
    delete api;

}


