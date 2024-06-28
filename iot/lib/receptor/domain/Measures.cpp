//
// Created by clement.mathe on 27/06/2024.
//

#include "Measures.h"


using namespace measure;

void Measures::deserializeMeasureFromBytes(const std::vector<uint8_t> &data) {
    if (data.empty() || data.size() < 4) {
        return;
    }


    // Récupération de l'ID
    std::vector<bool> serializedId = serializeIdToBits(data);
    uint32_t id = bitsToInteger(serializedId, 0, 32);

#ifdef RECEPTOR_DEBUG
    Serial.print("ID : ");
    Serial.println(id);
    Utils::printBytesAsIntegers(data);
#endif

    if (id == EMITTER_ID) {
        std::vector<bool> serializedBits = serializeMeasuresToBits(data);



        // Définition des longueurs de bits pour chaque mesure
        int pos = 0;

        Heltec.display->clear();

        for (const std::shared_ptr<AbstractMeasure> &measure: measures) {
            uint32_t value = bitsToInteger(serializedBits, pos, measure->dateLength);
            measure->setRawMeasure(value);
            pos += measure->dateLength;
        }
    } else {
        Serial.println("ID non reconnu");
    }
}

std::vector<bool> Measures::serializeIdToBits(const std::vector<uint8_t> &data) {
    std::vector<bool> bitsId;

    for (size_t i = 0; i < 4; ++i) { //
        for (int j = 7; j >= 0; --j) {
            bitsId.push_back((data[i] >> j) & 1);
        }
    }
    return bitsId;
}

// Simule l'obtention des mesures sérialisées en bits
std::vector<bool> Measures::serializeMeasuresToBits(const std::vector<uint8_t> &data) {
    std::vector<bool> measureBits;

    for (size_t i = 5; i < data.size(); ++i) { // Commencer à partir de l'indice 1 pour ignorer le premier byte
        for (int j = 7; j >= 0; --j) {
            measureBits.push_back((data[i] >> j) & 1);
        }
    }
    return measureBits;
}

// Convertit un segment de bits en un entier
uint32_t Measures::bitsToInteger(const std::vector<bool> &bits, int start, int length) {
    uint32_t result = 0;
    for (int i = 0; i < length; ++i) {
        result = (result << 1) | bits[start + i];
    }
    return result;
}

uint32_t Measures::bytesToUInt32(const std::vector<uint8_t> &data, int start) {
    if (start + 4 > data.size()) {
        // Assurez-vous que nous avons suffisamment de bytes pour lire un uint32_t
        return 0;
    }
    return (static_cast<uint32_t>(data[start]) << 24) |
           (static_cast<uint32_t>(data[start + 1]) << 16) |
           (static_cast<uint32_t>(data[start + 2]) << 8) |
           static_cast<uint32_t>(data[start + 3]);
}

Measures::Measures() {
    measures = std::vector<std::shared_ptr<AbstractMeasure>>();

}

void Measures::addMeasure(const std::shared_ptr<AbstractMeasure> &measure) {
    measures.push_back(measure);
}
