//
// Created by clement.mathe on 19/04/2024.
//

#include "Sensors.h"

void Sensors::addSensor(std::shared_ptr<AbstractSensor> sensor) {
    sensors.push_back(std::move(sensor));
}

void Sensors::begin() {
    for (auto &sensor: sensors) {
        sensor->begin();
    }
}

uint8_t Sensors::getSerializedMeasures() {
    for (auto &sensor: sensors) {
        sensor->getSerializeMeasure();
    }}

void Sensors::getMeasures() {
    for (auto &sensor: sensors) {
        sensor->getMeasure();
    }
}

uint8_t Sensors::serialize() {
    return 0;
}
