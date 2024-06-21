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
   deserializeMeasureFromBytes(bytesToSent);

    Utils::printBytesAsIntegers(bytesToSent);
    return bytesToSent;
}




uint16_t Sensors::deserializeMeasureFromBytes(const std::vector<uint8_t>& data) {
    if (data.empty()) {
        return 0;
    }

//    int datasBitLength[] = {12,12,12,12,8};
//    int bitPos = 8; // Commence à 8 pour ignorer le premier byte
//
//    for (int length : datasBitLength) {
//        uint32_t extractedValue = extractBits(data, bitPos, length);
//        std::cout << "Valeur extraite : " << extractedValue << " (";
//        std::cout << std::bitset<32>(extractedValue).to_string().substr(32-length, length) << ")" << std::endl;
//    }
//    uint16_t measure = 0;
    std::vector<bool> serializedBits = serializeMeasuresToBits(data);

    // Définition des longueurs de bits pour chaque mesure
    int datasBitLength[] = {12, 12, 12, 12, 8};
    int pos = 0;

    for (int length : datasBitLength) {
        uint32_t value = bitsToInteger(serializedBits, pos, length);
        std::cout << "Valeur extraite : " << value << " (";
        for (int i = pos; i < pos + length; ++i) {
            std::cout << serializedBits[i];
        }
        std::cout << ")" << std::endl;
        pos += length;
    }
    return 0;
}

// Simule l'obtention des mesures sérialisées en bits
std::vector<bool> Sensors::serializeMeasuresToBits(const std::vector<uint8_t>& data) {
    std::vector<bool> bits;
    for (size_t i = 1; i < data.size(); ++i) { // Commencer à partir de l'indice 1 pour ignorer le premier byte
        for (int j = 7; j >= 0; --j) {
            bits.push_back((data[i] >> j) & 1);
        }
    }
    return bits;
}

// Convertit un segment de bits en un entier
uint32_t Sensors::bitsToInteger(const std::vector<bool>& bits, int start, int length) {
    uint32_t result = 0;
    for (int i = 0; i < length; ++i) {
        result = (result << 1) | bits[start + i];
    }
    return result;
}

void Sensors::getMeasures() {
    for (auto &sensor: sensors) {
        sensor->getMeasure();
    }
}

uint8_t Sensors::serialize() {
    return 0;
}
