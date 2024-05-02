//
// Created by clement.mathe on 12/04/2024.
//

#ifndef T_IOT_902_SENSORSENSEI_DEVICEMANAGER_H
#define T_IOT_902_SENSORSENSEI_DEVICEMANAGER_H

#include <vector>
#include <memory>
#include "manager/PowerManger//PowerManager.h"
#include "manager/CommunicationManager/LoRaCommunicationManager.h"
#include "domain/deviceInfos/DeviceInfos.h"
#include "domain/Sensor/ISensor.h"
#include "domain/Sensor/AbstractSensor.h"
#include "domain/Sensor/Sensors.h"

using namespace sensor;

class EmitterDeviceManager {
private:
private:
    std::unique_ptr<PowerManager> powerManager{};
    std::unique_ptr<LoRaCommunicationManager> communicationManager;
    std::unique_ptr<Sensors> sensors;
public:
    DeviceInfos deviceInfo;
    EmitterDeviceManager();

    void init() const;
    void loop() const;
    void communicateMeasures();
    void communicateInfos();


    void beginSensor();
};


#endif //T_IOT_902_SENSORSENSEI_DEVICEMANAGER_H
