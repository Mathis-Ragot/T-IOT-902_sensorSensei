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

using namespace sensor;

class EmitterDeviceManager {

public:
    DeviceInfos deviceInfo;
    PowerManager powerManager;
    LoraCommunicationManager communicationManager;
    std::vector<std::shared_ptr<AbstractSensor>> sensors; // shared_ptr to avoid memory leak

    EmitterDeviceManager();

    void init();
    void loop();
    void addSensor(std::shared_ptr<AbstractSensor> sensor);
    void sendMeasures();
    void sendInfos();



};


#endif //T_IOT_902_SENSORSENSEI_DEVICEMANAGER_H
