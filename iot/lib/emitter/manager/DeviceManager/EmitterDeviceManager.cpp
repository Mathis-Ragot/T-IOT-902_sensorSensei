//
// Created by clement.mathe on 12/04/2024.
//

#include "EmitterDeviceManager.h"
#include "domain/Sensor/Dust/DustSensor.h"
#include "domain/Sensor/Sensors.h"



void EmitterDeviceManager::init() {

    deviceInfo = DeviceInfos(EMITTER_ID, EMITTER_TYPE, EMITTER_LOCATION, EMITTER_LATITUDE, EMITTER_LONGITUDE);

    sensors = new Sensors();
    sensors->addSensor(std::make_shared<DustSensor>());

    sensors->begin();
}

void EmitterDeviceManager::loop() const {
//        sensors->getMeasures();
        sensors->getSerializedMeasuresAsBytes();
        delay(400);
}

void EmitterDeviceManager::communicateMeasures() {

}

void EmitterDeviceManager::communicateInfos() {

}







