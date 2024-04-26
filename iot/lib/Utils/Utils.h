//
// Created by clement.mathe on 26/04/2024.
//

#ifndef IOT_UTILS_H
#define IOT_UTILS_H

#include <Arduino.h>

class Utils {
public:
    static void printBits(int value, int numBits);
    static int countSignificantBits(int value);
};

#endif //IOT_UTILS_H
