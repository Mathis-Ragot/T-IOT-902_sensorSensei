//
// Created by clement.mathe on 12/04/2024.
//

#ifndef T_IOT_902_SENSORSENSEI_DEVICEMANAGER_H
#define T_IOT_902_SENSORSENSEI_DEVICEMANAGER_H

#include <vector>
#include <memory>
#include "powerManager/PowerManager.h"
#include "LoRaCommunicationManager.h"
#include "DeviceInfos.h"
#include "domain/Sensor/ISensor.h"
#include "domain/Sensor/AbstractSensor.h"
#include "domain/Sensor/Sensors.h"
#include "domain/Sensor/Dust/DustSensor.h"
#include "domain/Sensor/Temperature/TemperatureSensor.h"
#include "domain/Sensor/Pressure/PressureSensor.h"
#include "domain/Sensor/Humidity/HumiditySensor.h"
#include "domain/Sensor/Sound/SoundSensor.h"
#include "infrastructure/lora/LoraEmitterManager.h"


class EmitterDeviceManager {
public:
    DeviceInfos deviceInfo;

    /**
     * @brief Constructor of the EmitterDeviceManager class.
     * Initializes device information, power manager, communication manager, and sensors.
     *
     * @param loraInstance Reference to an instance of LoRaClass used for LoRa communication.
     */
    explicit EmitterDeviceManager(LoRaClass &loraInstance);

    /**
    * @brief Initialization method for the EmitterDeviceManager.
    * Initializes the power manager, communication manager, and sensors.
    */
    void init() const;

    /**
     * @brief Main loop method for the EmitterDeviceManager.
     * Collects sensor measurements, adds the device ID, and sends the data via LoRa.
     */
    void loop() const;

    /**
     * @brief Method to communicate measures.
     * Currently not implemented.
     */
    void communicateMeasures();


    /**
     * @brief Method to communicate information.
     * Currently not implemented.
     */
    void communicateInfos();

private:
    std::unique_ptr<PowerManager> powerManager{};
    std::unique_ptr<LoRaCommunicationManager> communicationManager;
    std::unique_ptr<Sensors> sensors;
};


#endif //T_IOT_902_SENSORSENSEI_DEVICEMANAGER_H
