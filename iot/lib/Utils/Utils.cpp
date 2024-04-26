//
// Created by clement.mathe on 26/04/2024.
//

#include "Utils.h"

void Utils::printBits(int value, int numBits) {
    Serial.print("Bits: ");
    for (int i = numBits - 1; i >= 0; --i) {
        Serial.print((value >> i) & 1);
    }
    Serial.println();
}

int Utils::countSignificantBits(int value) {
    int bits = 0;
    while (value > 0) {
        bits++;
        value >>= 1;
    }
    Serial.print("Bits: ");
    Serial.print(bits);
    return bits;
}
// Path: lib/Utils/Utils.h
