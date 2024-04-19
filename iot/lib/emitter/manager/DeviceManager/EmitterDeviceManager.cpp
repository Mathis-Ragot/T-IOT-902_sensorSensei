//
// Created by clement.mathe on 12/04/2024.
//

#include "EmitterDeviceManager.h"
#include "domain/Sensor/DustSensor.h"

EmitterDeviceManager::EmitterDeviceManager() = default;

void EmitterDeviceManager::init() {

    deviceInfo = DeviceInfos(EMITTER_ID, EMITTER_TYPE, EMITTER_LOCATION, EMITTER_LATITUDE, EMITTER_LONGITUDE);

//DUST SENSOR
    std::shared_ptr<AbstractSensor> mySensor = std::make_shared<DustSensor>(
            SensorInfos(
                    DUST_SENSOR_ID,
                    DUST_SENSOR_REF,
                    std::vector<SensorType>{SensorInfos::stringToSensorType(DUST_SENSOR_TYPE)}
            )
    );
    addSensor(mySensor);

    for (auto &sensor: sensors) {
        sensor->begin();
    }
}

void EmitterDeviceManager::loop() {

    for (auto &sensor: sensors) {
        sensor->getMeasure();
        delay(400);
    }


}

void EmitterDeviceManager::sendMeasures() {

}

void EmitterDeviceManager::sendInfos() {

}

void EmitterDeviceManager::addSensor(std::shared_ptr<AbstractSensor> sensor) {
    sensors.push_back(std::move(sensor));
}


