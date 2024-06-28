//
// Created by clement.mathe on 27/06/2024.
//

#include "Measures.h"


using namespace measure;

void Measures::deserializeMeasureFromBytes(const std::vector<uint8_t> &data) {
    if (data.empty()) {
        return ;
    }
    std::vector<bool> serializedBits = serializeMeasuresToBits(data);

    // Définition des longueurs de bits pour chaque mesure
//    int datasBitLength[] = {12, 12, 12, 12, 8};
    int pos = 0;
//    int y = 0;

    Heltec.display->clear();

    for(const std::shared_ptr<AbstractMeasure>& measure : measures){
        uint32_t value =  bitsToInteger(serializedBits, pos, measure->dateLength);
        measure->setRawMeasure(value);
        pos += measure->dateLength;
    }
//
//    for (int length: datasBitLength) {
//        uint32_t value = bitsToInteger(serializedBits, pos, length);
//        std::string bitString = "";
//        for (int i = pos; i < pos + length; ++i) {
//            bitString += (serializedBits[i] ? "1" : "0");
//        }
//        pos += length;
//
//        std::string displayText = "Valeur extraite: " + std::to_string(value) + " (" + bitString + ")";
//        std::cout << displayText << std::endl;
//
//        Heltec.display->drawString(0, y, String(displayText.c_str()));
//        y += 10; // Ajuster l'espacement en fonction de vos besoins
//    }
//
//    Heltec.display->display();

}

// Simule l'obtention des mesures sérialisées en bits
std::vector<bool> Measures::serializeMeasuresToBits(const std::vector<uint8_t> &data) {
    std::vector<bool> bits;
    for (size_t i = 1; i < data.size(); ++i) { // Commencer à partir de l'indice 1 pour ignorer le premier byte
        for (int j = 7; j >= 0; --j) {
            bits.push_back((data[i] >> j) & 1);
        }
    }
    return bits;
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

void Measures::addMeasure(const std::shared_ptr<AbstractMeasure>& measure)  {
    measures.push_back(measure);
}
