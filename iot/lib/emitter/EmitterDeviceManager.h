//
// Created by clement.mathe on 12/04/2024.
//

#ifndef T_IOT_902_SENSORSENSEI_DEVICEMANAGER_H
#define T_IOT_902_SENSORSENSEI_DEVICEMANAGER_H

#include <vector>
#include <memory>
#include "powerManger/PowerManager.h"
//#include "infrastructure/CommunicationManager/LoRaCommunicationManager.h"
#include "../Shared/src/infrastructure/CommunicationManager/LoRaCommunicationManager.h"
#include "../Shared/src/domain/deviceInfos/DeviceInfos.h"
#include "domain/Sensor/ISensor.h"
#include "domain/Sensor/AbstractSensor.h"
#include "domain/Sensor/Sensors.h"
#include "domain/Sensor/Dust/DustSensor.h"
#include "domain/Sensor/Temperature/TemperatureSensor.h"
#include "domain/Sensor/Pressure/PressureSensor.h"
#include "domain/Sensor/Sound/SoundSensor.h"
#include "infrastructure/lora/LoraEmitterManager.h"


using namespace sensor;

class EmitterDeviceManager {
private:
private:
    std::unique_ptr<PowerManager> powerManager{};
    std::unique_ptr<LoRaCommunicationManager> communicationManager;
    std::unique_ptr<Sensors> sensors;
public:
    DeviceInfos deviceInfo;
    explicit EmitterDeviceManager(LoRaClass &loraInstance);

    void init() const;
    void loop() const;
    void communicateMeasures();
    void communicateInfos();


    void beginSensor();
};


#endif //T_IOT_902_SENSORSENSEI_DEVICEMANAGER_H
