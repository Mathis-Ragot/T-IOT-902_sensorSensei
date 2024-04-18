//
// Created by clement.mathe on 12/04/2024.
//

#include "DeviceInfos.h"
#include "../DeviceType.h"
#include "vector"

DeviceInfos::DeviceInfos(int deviceID, std::vector<DeviceType> deviceBoardType) {
    this->deviceID = deviceID;
    this->deviceBoardType = deviceBoardType;
}