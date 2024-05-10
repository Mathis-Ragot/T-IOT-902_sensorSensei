//
// Created by clement.mathe on 12/04/2024.
//

#include "DeviceInfos.h"

DeviceInfos::DeviceInfos(

        int deviceID,
        std::string deviceName,
        std::string deviceLocation,
        double latitude,
        double longitude) {

    this->deviceID = deviceID;
    this->deviceType = std::move(deviceName);
    this->deviceLocation = std::move(deviceLocation);
    this->latitude = latitude;
    this->longitude = longitude;

}
