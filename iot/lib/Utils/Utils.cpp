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

void Utils::printBytesAsCharacters(const std::vector<uint8_t>& bytes) {
    Serial.print( "Characters: ");
    for (uint8_t byte : bytes) {
        if (isprint(byte))  // Vérifie si le byte est un caractère imprimable
            Serial.print(static_cast<char>(byte));
        else
            Serial.print('.');  // Afficher un point pour les caractères non imprimables
    }
    Serial.println();
}

void Utils::printBytesAsIntegers(const std::vector<uint8_t>& bytes) {
    Serial.print("Bytes: ");
    for (uint8_t byte : bytes) {
        if (byte < 10) Serial.print("00");  // Pour aligner les chiffres pour les nombres en dessous de 10
        else if (byte < 100) Serial.print("0");  // Pour aligner les chiffres pour les nombres en dessous de 100
        Serial.print(byte);
        Serial.print(" ");
    }
    Serial.println();
}

void Utils::printBytesAsHex(const std::vector<uint8_t>& bytes) {
    Serial.print("Hex Bytes: ");
    for (uint8_t byte : bytes) {
        if (byte < 16) Serial.print("0");  // Ajouter un zéro pour l'alignement des nombres hexadécimaux
        Serial.print(byte, HEX);
        Serial.print(" ");
    }
    Serial.println();
}
// Path: lib/Utils/Utils.h
