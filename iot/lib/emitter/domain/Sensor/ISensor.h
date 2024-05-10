//
// Created by clement.mathe on 11/04/2024.
//

#ifndef T_IOT_902_SENSORSENSEI_ISENSOR_H
#define T_IOT_902_SENSORSENSEI_ISENSOR_H

#include "domain/SensorInfos/SensorInfos.h"
#include <cstdint>
#include <vector>

namespace sensor {

}
    class ISensor {

    public:

        virtual void begin() = 0;

        virtual float getMeasure() = 0;

        virtual uint16_t getSerializedMeasure() = 0;

        virtual ~ISensor() = default;


};
#endif //T_IOT_902_SENSORSENSEI_ISENSOR_H
