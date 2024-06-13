//
// Created by clement.mathe on 12/04/2024.
//

#ifndef T_IOT_902_SENSORSENSEI_DEVICEMANAGER_H
#define T_IOT_902_SENSORSENSEI_DEVICEMANAGER_H

#include <vector>
#include <memory>
#include "powerManger/PowerManager.h"
#include "LoRaCommunicationManager.h"
#include "DeviceInfos.h"
#include "domain/Sensor/ISensor.h"
#include "domain/Sensor/AbstractSensor.h"
#include "domain/Sensor/Sensors.h"
#include "domain/Sensor/Dust/DustSensor.h"
#include "domain/Sensor/Temperature/TemperatureSensor.h"
#include "domain/Sensor/Pressure/PressureSensor.h"
#include "domain/Sensor/Sound/SoundSensor.h"
#include "infrastructure/lora/LoraEmitterManager.h"
#include "Adafruit_BMP280.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "ExampleObserverReceptor.h"

using namespace sensor;

class EmitterDeviceManager {
private:
private:
    std::unique_ptr<PowerManager> powerManager{};
    LoRaCommunicationManager* communicationManager;
    std::unique_ptr<Sensors> sensors;
    QueueHandle_t packetQueue;
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
