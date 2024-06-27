//
// Created by clement.mathe on 27/06/2024.
//

#ifndef IOT_DUSTMEASURE_H
#define IOT_DUSTMEASURE_H

#include "AbstractMeasure.h"
#include <Arduino.h>

namespace measure {

    class DustMeasure : public measure::AbstractMeasure {

    public:
        DustMeasure();

        ~DustMeasure() override = default;

        String getDeSerializedMeasure() override;
    };

}

#endif //IOT_DUSTMEASURE_H
