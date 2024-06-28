//
// Created by clement.mathe on 19/04/2024.
//

#include "Sensors.h"
#include "Utils.h"
#include <iostream>
#include <vector>
#include <bitset>

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
    std::vector<uint8_t> bytesToSent = {};
    uint8_t totalLength = 0;

    for (auto &sensor: sensors) {

        totalLength += sensor->dataBitLength;
        uint16_t measure = sensor->getSerializedMeasure();
        uint16_t mask = (1 << sensor->dataBitLength) - 1; //Masque pour conserver les n bits désirés
        uint16_t sensorMeasure = measure & mask;

        Serial.print("sensorMeasure >> i = ");
        // Store bits from most significant to least significant.
        for (int i = sensor->dataBitLength - 1; i >= 0; --i) {
            Serial.print((sensorMeasure >> i) & 1);
            serializedMeasures.push_back((sensorMeasure >> i) & 1);
        }
        Serial.println();
    }

    Serial.print("serializedMeasures = ");
    for (bool bit : serializedMeasures) {
        Serial.print(bit);
    }
    Serial.println();
    //Empaquetage des bits dans des bytesToSent
    bytesToSent.push_back(totalLength);
    // Pack bits into bytesToSent.
    for (size_t i = 0; i < serializedMeasures.size(); i += 8) {
        uint8_t byte = 0;
        for (size_t j = 0; j < 8 && i + j < serializedMeasures.size(); ++j) {
            byte |= serializedMeasures[i + j] << (7 - j); // Inverse l'ordre des bits dans le byte
        }


        //deserialisation

        bytesToSent.push_back(byte);
    }


    Utils::printBytesAsIntegers(bytesToSent);
    return bytesToSent;
}

void Sensors::getMeasures() {
    for (auto &sensor: sensors) {
        sensor->getMeasure();
    }
}

uint8_t Sensors::serialize() {
    return 0;
}
