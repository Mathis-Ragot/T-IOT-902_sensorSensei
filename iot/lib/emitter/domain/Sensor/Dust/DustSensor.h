//
// Created by clement.mathe on 18/04/2024.
//

#ifndef IOT_DUSTSENSOR_H
#define IOT_DUSTSENSOR_H

#include "Arduino.h"
#include <string>
#include <utility>
#include "Utils.h"
#include "domain/Sensor/AbstractSensor.h"
#include <iostream>
#include "cmath"

namespace sensor {

    class DustSensor : public AbstractSensor {

    public:

        explicit DustSensor();

        void begin() override;

        float getMeasure() override;

        void readMeasure(int sample);

        uint16_t getSerializedMeasure() override;

    private:
        int measurePin = DUST_MEASURE_PIN;
        int ledPower = DUST_LED_PIN;
        int adcResolution = 12;

        float covRatio = 0.2f;
        int noDustVoltage = 400;
        int sysVoltage = 3300;

        int adcValue;
        float voltage;
        float density;

        const int NUM_SAMPLES = 10;
        std::vector<int> adcValues = std::vector<int>(NUM_SAMPLES);
        int adcIndex = 0;
        int sumAdcValues = 0;
        int numReadings = 0;

        int samplingTime = 280;
        int deltaTime = 40;
        int sleepTime = 250;
    };

}
#endif //IOT_DUSTSENSOR_H
