//
// Created by clement.mathe on 06/06/2024.
//

#include "ReceptorApp.h"

ReceptorDeviceManager *deviceManager;
LoRaClass loraInstance;

ReceptorApp::ReceptorApp() {
    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/, false, LORA_FREQUENCY);

    deviceManager = new ReceptorDeviceManager(loraInstance);
    deviceManager->init();
}

ReceptorApp::~ReceptorApp() {
    delete deviceManager;
}

void ReceptorApp::loop() {
    deviceManager->loop();
}