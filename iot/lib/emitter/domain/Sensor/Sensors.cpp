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

std::vector<bool> Sensors::getSerializedMeasures() {

    std::vector<bool> serializedMeasures;
    for (auto &sensor: sensors) {
//        serializedMeasures.push_back(sensor->getSerializedMeasure());
    }

//    uint8_t result = 0;
//    for (auto &measure: serializedMeasures) {
//        // Assuming the measures are 8 bits and don't overlap
//        result = (result << 8) | measure;
//    }
//    return result;
    return serializedMeasures;
}

void Sensors::getMeasures() {
    for (auto &sensor: sensors) {
        sensor->getMeasure();
    }
}

uint8_t Sensors::serialize() {
    return 0;
}
