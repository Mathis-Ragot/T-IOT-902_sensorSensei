//
// Created by clement.mathe on 27/06/2024.
//

#ifndef IOT_SOUNDMEASURE_H
#define IOT_SOUNDMEASURE_H

#include "AbstractMeasure.h"
#include <Arduino.h>

namespace measure {


    class SoundMeasure : public measure::AbstractMeasure {

    public:
        SoundMeasure();

        ~SoundMeasure() override = default;

        String getDeSerializedMeasure() override;
    };
}

#endif //IOT_SOUNDMEASURE_H
