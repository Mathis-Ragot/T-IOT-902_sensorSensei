//
// Created by clement.mathe on 19/04/2024.
//

#ifndef IOT_ABSTRACTSENSOR_H
#define IOT_ABSTRACTSENSOR_H

#include "ISensor.h"

namespace sensor {

    class AbstractSensor : public ISensor {
    private:

    public:

        void begin() override = 0;

        float getMeasure() override = 0;

        std::vector<bool> getSerializedMeasure() override = 0;

        sensor::SensorInfos getInfos();

    protected:
        SensorInfos infos;
        explicit AbstractSensor() : infos(std::move(infos)) {}

    };


}
#endif //IOT_ABSTRACTSENSOR_H
