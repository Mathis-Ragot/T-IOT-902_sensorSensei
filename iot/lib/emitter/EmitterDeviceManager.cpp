//
// Created by clement.mathe on 12/04/2024.
//

#include "Adafruit_BMP280.h"
#include "EmitterDeviceManager.h"



EmitterDeviceManager::EmitterDeviceManager(LoRaClass &loraInstance)
        : deviceInfo(EMITTER_ID, EMITTER_TYPE, EMITTER_LOCATION, EMITTER_LATITUDE, EMITTER_LONGITUDE),
          powerManager(new PowerManager()),
          communicationManager(new LoraEmitterManager(loraInstance)),
          sensors(new Sensors) {}


void EmitterDeviceManager::init() const {
    PowerManager::init();
    communicationManager->init();

    sensors->addSensor(std::make_shared<DustSensor>());
    sensors->addSensor(std::make_shared<TemperatureSensor>());
    sensors->addSensor(std::make_shared<PressureSensor>());
    sensors->addSensor(std::make_shared<SoundSensor>());
    sensors->addSensor(std::make_shared<HumiditySensor>());
    sensors->begin();
}

void EmitterDeviceManager::loop() const {

    std::vector<uint8_t> measures = sensors->getSerializedMeasuresAsBytes();

    auto intToAdd = (uint32_t)deviceInfo.deviceID;

    // Convertir l'entier en une séquence de bytes
    uint8_t byte1 = (intToAdd >> 24) & 0xFF;
    uint8_t byte2 = (intToAdd >> 16) & 0xFF;
    uint8_t byte3 = (intToAdd >> 8) & 0xFF;
    uint8_t byte4 = intToAdd & 0xFF;

    // Insérer les bytes au début du vecteur
    measures.insert(measures.begin(), byte1);
    measures.insert(measures.begin() + 1, byte2);
    measures.insert(measures.begin() + 2, byte3);
    measures.insert(measures.begin() + 3, byte4);

    Serial.println("serializedMeasures with DeviceId = ");
    Utils::printBytesAsIntegers(measures);
    Serial.println();




    communicationManager->send(measures.data(),measures.size() );
    PowerManager::deepSleep();
}

void EmitterDeviceManager::communicateMeasures() {

}

void EmitterDeviceManager::communicateInfos() {

}







