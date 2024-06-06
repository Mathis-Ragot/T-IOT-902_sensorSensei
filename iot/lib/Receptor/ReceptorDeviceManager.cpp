//
// Created by clement.mathe on 06/06/2024.
//

#include "ReceptorDeviceManager.h"
#include "ExampleObserverReceptor.h"

ReceptorDeviceManager::ReceptorDeviceManager(LoRaClass &loraInstance) :
        deviceInfo(DeviceInfos(RECEPTOR_ID, RECEPTOR_TYPE, RECEPTOR_LOCATION, RECEPTOR_LATITUDE, RECEPTOR_LONGITUDE)),
        communicationManager(new LoraReceptorManager(loraInstance)) {}

void ReceptorDeviceManager::init() const {

    communicationManager->init();

    auto *observer = new ExampleObserverReceptor();
    communicationManager->addObserver(observer);
}

void ReceptorDeviceManager::loop() const {

    communicationManager->receive();



    ;}

void ReceptorDeviceManager::communicateMeasures() {

}

void ReceptorDeviceManager::communicateInfos() {

}


