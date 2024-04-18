//
// Created by clement.mathe on 11/04/2024.
//

#ifndef T_IOT_902_SENSORSENSEI_ISENSOR_H
#define T_IOT_902_SENSORSENSEI_ISENSOR_H

#include "SensorType.h"

class ISensor {
public:
    virtual void setup() = 0;

    virtual void setFrequency(int frequency) = 0;

    virtual void setPin(int pins) = 0;

    virtual void setThreshold(int threshold) = 0;

    virtual void setCallback(void (*callback)(int)) = 0;

    virtual void start() = 0;

    virtual void stop() = 0;

    virtual SensorType getType() = 0;

private:
    int frequency;
    int pins;
    int threshold;
    void (*callback)(int);
    SensorType type;


};

#endif //T_IOT_902_SENSORSENSEI_ISENSOR_H
