//
// Created by clement.mathe on 12/04/2024.
//

#ifndef T_IOT_902_SENSORSENSEI_DEVICEINFOS_H
#define T_IOT_902_SENSORSENSEI_DEVICEINFOS_H

#include <string>
#include <utility>
#include "vector"

class DeviceInfos {
public:

    DeviceInfos(int deviceID, std::string deviceName, std::string deviceLocation,
                double latitude, double longitude);

    int deviceID{};
    std::string deviceType;
    std::string deviceLocation;
    double latitude{};
    double longitude{};

    DeviceInfos()= default;




};


#endif //T_IOT_902_SENSORSENSEI_DEVICEINFOS_H
