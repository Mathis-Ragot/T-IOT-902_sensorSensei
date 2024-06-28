//
// Created by clement.mathe on 27/06/2024.
//

#ifndef IOT_IMEASURE_H
#define IOT_IMEASURE_H

#include <cstdint>
#include <Arduino.h>

class IMeasure {
private :
    uint32_t rawMeasure;
    int dateLength;

public:
    virtual void setRawMeasure(uint32_t rawMeasure) = 0;
    virtual String getDeSerializedMeasure() = 0;

    virtual ~IMeasure() = default;
};

#endif //IOT_IMEASURE_H
