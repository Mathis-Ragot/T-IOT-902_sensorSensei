//
// Created by clement.mathe on 18/04/2024.
//

#ifndef IOT_DUSTSENSOR_H
#define IOT_DUSTSENSOR_H

#include "ISensor.h"
#include "../SensorInfos/SensorInfos.h"
#include "Arduino.h"
#include "AbstractSensor.h"
#include <string>
#include <utility>



namespace sensor {

    class DustSensor : public AbstractSensor {

    public:

        explicit DustSensor();

        void begin() override;

        float getMeasure() override;

//        SensorInfos getInfos() override;

    private:
        int measurePin = DUST_MEASURE_PIN;
        int ledPower = DUST_LED_PIN;

        int samplingTime = 280;
        int deltaTime = 40;
        int sleepTime = 9680;

        float voMeasured = 0;
        float calcVoltage = 0;
        float dustDensity = 0;
    };

}
#endif //IOT_DUSTSENSOR_H
