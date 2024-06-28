//
// Created by clement.mathe on 26/04/2024.
//

#include <iostream>
#include "Utils.h"

void Utils::printBits(int value, int numBits) {
    std::cout << "Bits: ";
    for (int i = numBits - 1; i >= 0; --i) {
        std::cout << "Bits: " << ((value >> i) & 1);
    }
    std::cout << std::endl;
}

int Utils::countSignificantBits(int value) {
    int bits = 0;
    while (value > 0) {
        bits++;
        value >>= 1;
    }
    std::cout << "Bits: " << bits << std::endl;
    return bits;
}

void Utils::printBytesAsCharacters(const std::vector<uint8_t>& bytes) {
    std::cout << "Characters: ";
    for (uint8_t byte : bytes) {
        if (isprint(byte))  // Vérifie si le byte est un caractère imprimable
            std::cout << static_cast<char>(byte);
        else
            std::cout << '.';  // Afficher un point pour les caractères non imprimables
    }
    std::cout << std::endl;
}

void Utils::printBytesAsIntegers(const std::vector<uint8_t>& bytes) {
    std::cout << "Bytes: ";
    for (uint8_t byte : bytes) {
        if (byte < 10) {
            std::cout << "00"; // Pour aligner les chiffres pour les nombres en dessous de 10
        } else if (byte < 100) {
            std::cout << "0";  // Pour aligner les chiffres pour les nombres en dessous de 100
        };
        std::cout << byte << " ";
    }
    std::cout << std::endl;
}

void Utils::printBytesAsHex(const std::vector<uint8_t>& bytes) {
    std::cout << "Hex Bytes: ";
    for (uint8_t byte : bytes) {
        if (byte < 16) {
            std::cout << "0"; // Ajouter un zéro pour l'alignement des nombres hexadécimaux
        }
        std::cout << byte << " ";
    }
    std::cout << std::endl;
}