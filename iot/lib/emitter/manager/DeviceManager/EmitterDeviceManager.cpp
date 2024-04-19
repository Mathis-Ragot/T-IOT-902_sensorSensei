//
// Created by clement.mathe on 12/04/2024.
//

#include "EmitterDeviceManager.h"
#include "domain/Sensor/DustSensor.h"

EmitterDeviceManager::EmitterDeviceManager() = default;

void EmitterDeviceManager::init() {

    deviceInfo = DeviceInfos(EMITTER_ID, EMITTER_TYPE, EMITTER_LOCATION, EMITTER_LATITUDE, EMITTER_LONGITUDE);

    addSensor(std::make_shared<DustSensor>());
    beginSensor();
}

void EmitterDeviceManager::loop() {

    for (auto &sensor: sensors) {
        sensor->getMeasure();
        delay(400);
    }
}

void EmitterDeviceManager::communicateMeasures() {

}

void EmitterDeviceManager::communicateInfos() {

}

void EmitterDeviceManager::addSensor(std::shared_ptr<AbstractSensor> sensor) {
    sensors.push_back(std::move(sensor));
}

void EmitterDeviceManager::beginSensor() {
    for (auto &sensor: sensors) {
        sensor->begin();
    }
}



