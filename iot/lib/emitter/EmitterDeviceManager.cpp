//
// Created by clement.mathe on 12/04/2024.
//

#include "Adafruit_BMP280.h"
#include "EmitterDeviceManager.h"



EmitterDeviceManager::EmitterDeviceManager(LoRaClass &loraInstance)
        : deviceInfo(EMITTER_ID, EMITTER_TYPE, EMITTER_LOCATION, EMITTER_LATITUDE, EMITTER_LONGITUDE),
          powerManager(new PowerManager()),
          communicationManager(new LoraEmitterManager(loraInstance)),
          sensors(new Sensors) {}


void EmitterDeviceManager::init() const {

    powerManager->init();
    communicationManager->init();

    sensors->addSensor(std::make_shared<DustSensor>());
    sensors->addSensor(std::make_shared<TemperatureSensor>());
    sensors->addSensor(std::make_shared<PressureSensor>());
    sensors->addSensor(std::make_shared<SoundSensor>());
    sensors->begin();

    esp_sleep_enable_timer_wakeup(WAKE_UP_BOARD_DELAY);  // Réveil tous les 5 secondes
    pinMode(GPIO_PIN4_WAKEUP_ENABLE_S, INPUT);
}

void EmitterDeviceManager::loop() const {

    communicationManager->send(sensors->getSerializedMeasuresAsBytes().data(),sensors->getSerializedMeasuresAsBytes().size() );

    esp_deep_sleep_start();
}

void EmitterDeviceManager::communicateMeasures() {

}

void EmitterDeviceManager::communicateInfos() {

}







