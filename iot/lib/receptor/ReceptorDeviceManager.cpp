//
// Created by clement.mathe on 06/06/2024.
//

#include "ReceptorDeviceManager.h"
#include "MyHttpClient.h"
#include "infrastructure/wifi/ArduinoWifiClient.h"

ReceptorDeviceManager::ReceptorDeviceManager(LoRaClass &loraInstance) :
        deviceInfo(DeviceInfos(RECEPTOR_ID, RECEPTOR_TYPE, RECEPTOR_LOCATION, RECEPTOR_LATITUDE, RECEPTOR_LONGITUDE)) {

    packetQueue = xQueueCreate(30, sizeof(std::vector<uint8_t>*));
    communicationManager = new LoraReceptorManager(loraInstance, packetQueue);
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

void ReceptorDeviceManager::loop() const {
//    communicationManager->receive();
    std::vector<uint8_t>* receivedPacket;
    Heltec.display->clear();
    String displayData = "Received: ";

    if (xQueueReceive(packetQueue, &receivedPacket, portMAX_DELAY) == pdPASS) {
        // Traitement du paquet
        for (const auto &byte: *receivedPacket) {
            Serial.print(byte, HEX);
            Serial.print(" ");
            displayData += String(byte, HEX) + " ";
        }
        Serial.println();
        Heltec.display->drawString(0, 0, displayData);
        Heltec.display->display();
        // Libérer la mémoire après traitement
        delete receivedPacket;
    }

}

void ReceptorDeviceManager::communicateMeasures() {

}

void ReceptorDeviceManager::communicateInfos() {

}

ReceptorDeviceManager::~ReceptorDeviceManager() {
    delete wifiManager;
    delete api;
    vQueueDelete(packetQueue);

}


