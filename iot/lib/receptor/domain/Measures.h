//
// Created by clement.mathe on 27/06/2024.
//

#ifndef IOT_MEASURES_H
#define IOT_MEASURES_H

#include <cstdint>
#include "shared_mutex"
#include <vector>
#include <memory>
#include <iostream>
#include <Arduino.h>
#include "IMeasure.h"
#include "heltec.h"
#include "AbstractMeasure.h"
#include "Utils.h"


namespace measure {

    class Measures {

    public :
        Measures();

        std::vector<std::shared_ptr<AbstractMeasure>> measures ;

        void deserializeMeasureFromBytes(const std::vector<uint8_t> &data);
        void addMeasure(const std::shared_ptr<AbstractMeasure>& measure) ;

    private:

        std::vector<bool> serializeMeasuresToBits(const std::vector<uint8_t> &data);

        uint32_t bitsToInteger(const std::vector<bool> &bits, int start, int length);

        uint32_t bytesToUInt32(const std::vector<uint8_t>& data, int start);

        std::vector<bool> serializeIdToBits(const std::vector<uint8_t> &data);
    };
}
#endif //IOT_MEASURES_H
