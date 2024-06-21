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
   deserializeMeasureFromBytes(bytesToSent, 56);

    Utils::printBytesAsIntegers(bytesToSent);
    return bytesToSent;
}
uint32_t extractBits(const std::vector<uint8_t>& bytes, int startBit, int bitLength) {
    uint32_t result = 0;
    int byteIndex = startBit / 8; // Calcule l'index de l'octet de départ
    int bitIndex = startBit % 8; // Calcule le bit de départ dans l'octet
    int bitsCollected = 0;

    Serial.print("byteIndex = ");
    Serial.println(byteIndex);
    Serial.print("bitIndex = ");
    Serial.println(bitIndex);




    while (bitsCollected < bitLength) {
        int bitsInThisByte = std::min(bitLength - bitsCollected, 8 - bitIndex);
        uint32_t mask = (1 << bitsInThisByte) - 1; // Crée un masque pour les bits nécessaires dans cet octet
        uint32_t bits = (bytes[byteIndex] >> bitIndex) & mask; // Extrait les bits nécessaires et les place à droite
        result |= (bits << bitsCollected); // Place les bits extraits dans le résultat, décalés correctement
        bitsCollected += bitsInThisByte; // Met à jour le nombre de bits collectés
        bitIndex = 0; // Réinitialise le bitIndex pour le prochain octet
        byteIndex++; // Passe à l'octet suivant
    }

    Serial.print("bitsCollected = ");
    Serial.println(bitsCollected);

    Serial.print("result = ");
    Serial.println(result);

    return result;
}

uint16_t Sensors::deserializeMeasureFromBytes(const std::vector<uint8_t>& bytes, uint8_t dataBitLength) {
    if (bytes.empty()) {
        return 0;
    }

    int datasBitLength[] = {12,12,12,12,8};
    std::vector<bool> serializedMeasures;
    int a =0;
    for (int len : datasBitLength) {

        extractBits(bytes, a, len);
        a+=len;
    }
    // Convertir les octets en bits
    for (size_t i = 1; i < bytes.size(); ++i) { // Commence à 1 pour ignorer le premier octet (totalLength)
        uint8_t byte = bytes[i];
        for (int j = 0; j < 8; ++j) {
            serializedMeasures.push_back((byte >> j) & 1);
        }
    }

    // Reconstituer la mesure en uint16_t
    uint16_t measure = 0;
    for (int i = 0; i < dataBitLength && i < serializedMeasures.size(); ++i) {
        measure |= serializedMeasures[i] << i;
    }

    return measure;
}

void Sensors::getMeasures() {
    for (auto &sensor: sensors) {
        sensor->getMeasure();
    }
}

uint8_t Sensors::serialize() {
    return 0;
}
