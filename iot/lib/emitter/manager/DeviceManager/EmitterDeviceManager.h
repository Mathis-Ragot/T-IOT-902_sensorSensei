//
// Created by clement.mathe on 12/04/2024.
//

#ifndef T_IOT_902_SENSORSENSEI_DEVICEMANAGER_H
#define T_IOT_902_SENSORSENSEI_DEVICEMANAGER_H

#include <vector>
#include "manager/PowerManger//PowerManager.h"
#include "manager/CommunicationManager/LoraCommunicationManager.h"
#include "domain/deviceInfos/DeviceInfos.h"
#include "domain/Sensor/ISensor.h"


class EmitterDeviceManager {

public:
    DeviceInfos deviceInfo;
    PowerManager powerManager;
    LoraCommunicationManager communicationManager;
    std::vector<ISensor> sensors;

    EmitterDeviceManager();

    void init();


};


#endif //T_IOT_902_SENSORSENSEI_DEVICEMANAGER_H
