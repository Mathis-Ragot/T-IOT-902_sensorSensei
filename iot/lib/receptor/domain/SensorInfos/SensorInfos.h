//
// Created by clement.mathe on 12/04/2024.
//

#ifndef T_IOT_902_MEASURE_SENSORINFOS_H
#define T_IOT_902_MEASURE_SENSORINFOS_H

#include <vector>
#include <string>
#include "domain/SensorType.h"
#include "Measure.h"

namespace measure {

    class SensorInfos {

    public:

        SensorInfos(int sensorID, std::string sensorRef, std::vector<SensorType> sensorType);

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

         MeasureKind getMeasureKind() {
            switch(sensorType[0]){
                case SensorType::TEMPERATURE:
                    return MeasureKind::Temperature;
                case SensorType::HUMIDITY:
                    return MeasureKind::Humidity;
                case SensorType::AIR_QUALITY:
                    return MeasureKind::Dust;
                case SensorType::SOUND:
                    return MeasureKind::SoundLevel;
                case SensorType::PRESSURE:
                    return MeasureKind::Pressure;
                default:
                    return MeasureKind::Unknown;
            }
        }

         String sensorTypeToString(SensorType type) {
             switch (type) {
                 case SensorType::TEMPERATURE:
                     return "TEMPERATURE";
                 case SensorType::HUMIDITY:
                     return "HUMIDITY";
                 case SensorType::AIR_QUALITY:
                     return "AIR_QUALITY";
                 case SensorType::SOUND:
                     return "SOUND";
                 case SensorType::PRESSURE:
                     return "PRESSURE";
                 case SensorType::ALTITUDE:
                     return "ALTITUDE";
                 default:
                     return "UNKNOWN";
             }
         }
    };
}
#endif //T_IOT_902_MEASURE_SENSORINFOS_H
