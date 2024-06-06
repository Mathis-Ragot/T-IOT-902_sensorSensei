//
// Created by clavi on 03/05/2024.
//

#ifndef IOT_PRESSURESENSOR_H
#define IOT_PRESSURESENSOR_H

#include "../BMP280/BMP280Sensor.h"

namespace sensor {

    class PressureSensor : public BMP280Sensor {

    public:
        explicit PressureSensor();

        float getMeasure() override;

        uint16_t getSerializedMeasure() override;

    };

}

#endif //IOT_PRESSURESENSOR_H
