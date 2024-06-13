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
    sensors->begin();
}

void EmitterDeviceManager::loop() const {
    communicationManager->send(sensors->getSerializedMeasuresAsBytes().data(),sensors->getSerializedMeasuresAsBytes().size() );
    PowerManager::start();
}

void EmitterDeviceManager::communicateMeasures() {

}

void EmitterDeviceManager::communicateInfos() {

}







