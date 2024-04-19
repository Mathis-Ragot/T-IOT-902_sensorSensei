//
// Created by clement.mathe on 12/04/2024.
//

#ifndef T_IOT_902_SENSORSENSEI_SENSORINFOS_H
#define T_IOT_902_SENSORSENSEI_SENSORINFOS_H

#include "domain/Sensor/ISensor.h"
#include "../SensorType.h"
#include <vector>
#include <string>

namespace sensor {

    class SensorInfos {

    public:

        SensorInfos(int sensorID, std::string sensorRef, std::vector<SensorType> sensorType);

//        SensorInfos() = default;

        int sensorID{};
        std::string sensorRef{};
        std::vector<SensorType> sensorType;

        static SensorType stringToSensorType(const std::string &typeStr) {
            if (typeStr == "TEMPERATURE") return SensorType::TEMPERATURE;
            if (typeStr == "HUMIDITY") return SensorType::HUMIDITY;
            if (typeStr == "AIR_QUALITY") return SensorType::AIR_QUALITY;
            if (typeStr == "SOUND") return SensorType::SOUND;
            if (typeStr == "PRESSURE") return SensorType::PRESSURE;
            if (typeStr == "ALTITUDE") return SensorType::ALTITUDE;
            return SensorType::UNKNOWN;
        };
    };

}
#endif //T_IOT_902_SENSORSENSEI_SENSORINFOS_H
