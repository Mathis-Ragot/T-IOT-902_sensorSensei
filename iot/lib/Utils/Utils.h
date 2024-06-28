//
// Created by clement.mathe on 26/04/2024.
//

#ifndef IOT_UTILS_H
#define IOT_UTILS_H

#include "cstdint"
#include "vector"

class Utils {
public:
    static void printBits(int value, int numBits);
    static int countSignificantBits(int value);

    static void printBytesAsCharacters(const std::vector<uint8_t> &bytes);
    static void printBytesAsIntegers(const std::vector<uint8_t>& bytes);

    static void printBytesAsHex(const std::vector<uint8_t> &bytes);
};

#endif //IOT_UTILS_H
