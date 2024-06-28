//
// Created by clement.mathe on 27/06/2024.
//

#ifndef IOT_PRESSUREMEASURE_H
#define IOT_PRESSUREMEASURE_H

#include "AbstractMeasure.h"
#include <Arduino.h>
namespace measure {


    class PressureMeasure : public measure::AbstractMeasure {


    public:
        PressureMeasure();

        ~PressureMeasure() override = default;

        String getDeSerializedMeasure() override;

    };
}

#endif //IOT_PRESSUREMEASURE_H
