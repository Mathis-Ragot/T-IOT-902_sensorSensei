//
// Created by clement.mathe on 12/04/2024.
//

#include "Adafruit_BMP280.h"
#include "EmitterDeviceManager.h"
#include "domain/Sensor/Dust/DustSensor.h"
#include "domain/Sensor/Temperature/TemperatureSensor.h"
#include "domain/Sensor/Sensors.h"
#include "domain/Sensor/Pressure/PressureSensor.h"

EmitterDeviceManager::EmitterDeviceManager() :
        deviceInfo(DeviceInfos(EMITTER_ID, EMITTER_TYPE, EMITTER_LOCATION, EMITTER_LATITUDE, EMITTER_LONGITUDE)),
        powerManager(new PowerManager()),
        communicationManager(new LoRaCommunicationManager),
        sensors(new Sensors) {}


void EmitterDeviceManager::init() const {

    powerManager->init();
    //communicationManager->init();

    sensors->addSensor(std::make_shared<DustSensor>());
    sensors->addSensor(std::make_shared<TemperatureSensor>());
    sensors->addSensor(std::make_shared<PressureSensor>());
    sensors->begin();

    esp_sleep_enable_timer_wakeup(300000000);  // Réveil tous les 5 minutes
    pinMode(GPIO_PIN4_WAKEUP_ENABLE_S, INPUT);
}

void EmitterDeviceManager::loop() const {

    communicationManager->send(sensors->getSerializedMeasuresAsBytes().data());
    esp_deep_sleep_start()

    ;}

void EmitterDeviceManager::communicateMeasures() {

}

void EmitterDeviceManager::communicateInfos() {

}







