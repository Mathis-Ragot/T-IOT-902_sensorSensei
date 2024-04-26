//
// Created by clement.mathe on 19/04/2024.
//

#include "Sensors.h"
#include "Utils.h"

void Sensors::addSensor(std::shared_ptr<AbstractSensor> sensor) {
    sensors.push_back(std::move(sensor));
}

void Sensors::begin() {
    for (auto &sensor: sensors) {
        sensor->begin();
    }
}

std::vector<uint8_t> Sensors::getSerializedMeasuresAsBytes() {
    if (sensors.empty()) {
        return {};
    }
    std::vector<bool> serializedMeasures = {};
    for (auto &sensor: sensors) {
        uint16_t measure = sensor->getSerializedMeasure();
        uint16_t mask = (1 << sensor->dataBitLength) - 1; //Masque pour conserver les n bits désirés
        uint16_t sensorMeasure = measure & mask;

        // Store bits from least significant to most significant.
        for (int i = 0; i < sensor->dataBitLength; ++i) {
            serializedMeasures.push_back((sensorMeasure >> i) & 1);
        }

        //Empaquetage des bits dans des bytes
        std::vector<uint8_t> bytes;
        // Pack bits into bytes.
        for (size_t i = 0; i < serializedMeasures.size(); i += 8) {
            uint8_t byte = 0;
            for (size_t j = 0; j < 8 && i + j < serializedMeasures.size(); ++j) {
                byte |= serializedMeasures[i + j] << j;
            }
            bytes.push_back(byte);
        }

        return bytes;
    }
}
    void Sensors::getMeasures() {
        for (auto &sensor: sensors) {
            sensor->getMeasure();
        }
    }

    uint8_t Sensors::serialize() {
        return 0;
    }
