//
// Created by clement.mathe on 06/06/2024.
//

#ifndef IOT_EXAMPLEOBSERVERRECEPTOR_H
#define IOT_EXAMPLEOBSERVERRECEPTOR_H

#include <cstdint>
#include <cstdio>
#include "IPacketObserver.h"
#include "Arduino.h"

class ExampleObserverReceptor : public IPacketObserver {
public:
    void onPacketReceived(const uint8_t *data, size_t length) override {
        Serial.print("MyPacketObserver received packet: ");
        for (size_t i = 0; i < length; ++i) {
            Serial.print(data[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
        // Traitez le paquet comme nécessaire
    }
};



#endif //IOT_EXAMPLEOBSERVERRECEPTOR_H
