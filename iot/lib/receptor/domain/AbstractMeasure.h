//
// Created by clement.mathe on 27/06/2024.
//

#ifndef IOT_ABSTRACTMEASURE_H
#define IOT_ABSTRACTMEASURE_H

#include <cstdint>
#include <utility>
#include <Arduino.h>
#include "IMeasure.h"
#include "SensorInfos/SensorInfos.h"

namespace measure {

    class AbstractMeasure : public IMeasure {


    protected:
        uint32_t rawMeasure{};

        explicit AbstractMeasure(int dataLength, SensorInfos infos)
                : dateLength(dataLength), rawMeasure(0), infos(std::move(infos)) {} ;

        measure::SensorInfos infos;

    public:
        measure::SensorInfos getInfos() {
            return infos;
        };

        void setRawMeasure(uint32_t measure) override {
            rawMeasure = measure;
        };

        String getDeSerializedMeasure() override = 0;

        ~AbstractMeasure() override = default;

        int dateLength{};
    };


}
#endif //IOT_ABSTRACTMEASURE_H

