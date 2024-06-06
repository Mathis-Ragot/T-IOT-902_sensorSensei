//
// Created by clavi on 03/05/2024.
//

#ifndef IOT_TEMPERATURESENSOR_H
#define IOT_TEMPERATURESENSOR_H

#include "../BMP280/BMP280Sensor.h"

namespace sensor {

    class TemperatureSensor : public BMP280Sensor {

    public:
        explicit TemperatureSensor();

        float getMeasure() override;

        uint16_t getSerializedMeasure() override;

    };

}

#endif //IOT_TEMPERATURESENSOR_H
