//
// Created by clement.mathe on 27/06/2024.
//

#include "Measures.h"


using namespace measure;

bool Measures::checkAuthId(const std::vector<uint8_t> &data) {
    if (data.empty() || data.size() < 4) {
        return false;
    }
    // Récupération de l'ID
    std::vector<bool> serializedId = serializeIdToBits(data);
    uint32_t id = bitsToInteger(serializedId, 0, 32);

#ifdef RECEPTOR_DEBUG
    Serial.print("ID : ");
    Serial.println(id);
    Utils::printBytesAsIntegers(data);
#endif

    return id == EMITTER_ID;
}


void Measures::deserializeMeasureFromBytes(const std::vector<uint8_t> &data) {
    if (data.empty() || data.size() < 4) {
        return;
    }

    std::vector<bool> serializedBits = serializeMeasuresToBits(data);

    // Définition des longueurs de bits pour chaque mesure
    int pos = 0;

    Heltec.display->clear();

    for (const std::shared_ptr<AbstractMeasure> &measure: measures) {
        uint32_t value = bitsToInteger(serializedBits, pos, measure->dateLength);
        measure->setRawMeasure(value);
        pos += measure->dateLength;
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

Measures::Measures() {
    measures = std::vector<std::shared_ptr<AbstractMeasure>>();

}

void Measures::addMeasure(const std::shared_ptr<AbstractMeasure> &measure) {
    measures.push_back(measure);
}

extern "C" {
// Declare a function to get the free heap size
uint32_t getFreeHeap();
}

void printMemoryUsage() {
    uint32_t totalMemory = ESP.getHeapSize();  // Total heap size
    uint32_t freeMemory = ESP.getFreeHeap();   // Free heap size
    uint32_t usedMemory = totalMemory - freeMemory;
    float usedPercentage = ((float)usedMemory / totalMemory) * 100;

    Heltec.display->clear();
    Heltec.display->drawString(0, 0, "Memory Usage:");
    Heltec.display->drawString(0, 10, String(usedPercentage, 2) + "%");
    Heltec.display->display();
}