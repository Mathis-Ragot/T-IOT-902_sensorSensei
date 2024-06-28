//
// Created by clement.mathe on 27/06/2024.
//

#ifndef IOT_TEMPERATUREMEASURE_H
#define IOT_TEMPERATUREMEASURE_H

#include "AbstractMeasure.h"
#include <Arduino.h>

namespace measure {


    class TemperatureMeasure : public measure::AbstractMeasure {

    public:
        TemperatureMeasure();

        ~TemperatureMeasure() override = default;

        String getDeSerializedMeasure() override;
    };

}
#endif //IOT_TEMPERATUREMEASURE_H
