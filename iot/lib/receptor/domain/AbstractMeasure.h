//
// Created by clement.mathe on 27/06/2024.
//

#ifndef IOT_ABSTRACTMEASURE_H
#define IOT_ABSTRACTMEASURE_H

#include <cstdint>
#include <Arduino.h>
#include "IMeasure.h"

namespace measure {

    class AbstractMeasure : public IMeasure {


    protected:
        uint32_t rawMeasure{};

        explicit AbstractMeasure(int dataLength) : dateLength(dataLength), rawMeasure(0) {} ;

    public:
        void setRawMeasure(uint32_t measure) override {
            rawMeasure = measure;
        };

        String getDeSerializedMeasure() override = 0;

        ~AbstractMeasure() override = default;

        int dateLength{};
    };



}
#endif //IOT_ABSTRACTMEASURE_H

