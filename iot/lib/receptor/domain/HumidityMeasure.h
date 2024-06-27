//
// Created by clement.mathe on 27/06/2024.
//

#ifndef IOT_HUMIDITYMEASURE_H
#define IOT_HUMIDITYMEASURE_H

#include "AbstractMeasure.h"
#include <Arduino.h>

namespace measure {


    class HumidityMeasure : public measure::AbstractMeasure {

    public:
        HumidityMeasure();

        ~HumidityMeasure() override = default;

        String getDeSerializedMeasure() override;
    };


#endif //IOT_HUMIDITYMEASURE_H
}