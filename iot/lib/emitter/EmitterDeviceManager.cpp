//
// Created by clement.mathe on 12/04/2024.
//

#include "EmitterDeviceManager.h"
#include "infrastructure/lora/LoraReceptorManager.h"


EmitterDeviceManager::EmitterDeviceManager(LoRaClass &loraInstance)
        : deviceInfo(EMITTER_ID, EMITTER_TYPE, EMITTER_LOCATION, EMITTER_LATITUDE, EMITTER_LONGITUDE),
          powerManager(new PowerManager()),
          sensors(new Sensors) {
    packetQueue = xQueueCreate(10, sizeof(std::vector<uint8_t>));
    communicationManager = new LoraEmitterManager(loraInstance, packetQueue);
}

void EmitterDeviceManager::init() const {

    powerManager->init();
    communicationManager->init();

    sensors->addSensor(std::make_shared<DustSensor>());
    sensors->addSensor(std::make_shared<TemperatureSensor>());
    sensors->addSensor(std::make_shared<PressureSensor>());
    sensors->addSensor(std::make_shared<SoundSensor>());
    sensors->begin();

    auto *observer = new ExampleObserverReceptor();
    communicationManager->addObserver(observer);

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







