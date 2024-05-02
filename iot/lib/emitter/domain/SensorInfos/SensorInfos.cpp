//
// Created by clement.mathe on 12/04/2024.
//
#include "SensorInfos.h"

#include <utility>


sensor::SensorInfos::SensorInfos(int sensorID, std::string sensorRef, std::vector<SensorType> sensorType) : sensorID(sensorID), sensorRef(std::move(sensorRef)), sensorType(std::move(sensorType)){

}
