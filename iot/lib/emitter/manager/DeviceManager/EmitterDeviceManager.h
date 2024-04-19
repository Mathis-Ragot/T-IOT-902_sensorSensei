//
// Created by clement.mathe on 12/04/2024.
//

#ifndef T_IOT_902_SENSORSENSEI_DEVICEMANAGER_H
#define T_IOT_902_SENSORSENSEI_DEVICEMANAGER_H

#include <vector>
#include <memory>
#include "manager/PowerManger//PowerManager.h"
#include "manager/CommunicationManager/LoraCommunicationManager.h"
#include "domain/deviceInfos/DeviceInfos.h"
#include "domain/Sensor/ISensor.h"
#include "domain/Sensor/AbstractSensor.h"
#include "domain/Sensor/Sensors.h"

using namespace sensor;

class EmitterDeviceManager {

public:
    DeviceInfos deviceInfo;

    Sensors* sensors;

    PowerManager powerManager;
    LoraCommunicationManager communicationManager;

    EmitterDeviceManager()  = default;

    void init();
    void loop() const;
    void communicateMeasures();
    void communicateInfos();


    void beginSensor();
};


#endif //T_IOT_902_SENSORSENSEI_DEVICEMANAGER_H
