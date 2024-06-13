//
// Created by clement.mathe on 12/04/2024.
//

#ifndef T_IOT_902_SENSORSENSEI_POWERMANAGER_H
#define T_IOT_902_SENSORSENSEI_POWERMANAGER_H

#include "esp_sleep.h"
#include "Arduino.h"

class PowerManager {


public:
    PowerManager() = default;

    static void init();
    static void start();
};


#endif //T_IOT_902_SENSORSENSEI_POWERMANAGER_H
