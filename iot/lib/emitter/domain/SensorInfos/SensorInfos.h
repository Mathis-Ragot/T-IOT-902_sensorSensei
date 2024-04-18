//
// Created by clement.mathe on 12/04/2024.
//

#ifndef T_IOT_902_SENSORSENSEI_SENSORINFOS_H
#define T_IOT_902_SENSORSENSEI_SENSORINFOS_H

#include "domain/Sensor/ISensor.h"
#include "../SensorType.h"
#include <vector>

class SensorInfos {

public:
    int sensorID;
    std::vector<SensorType> sensorType;
    SensorInfos(int sensorID, std::vector<SensorType> sensorType);

};

#endif //T_IOT_902_SENSORSENSEI_SENSORINFOS_H
