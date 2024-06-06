//
// Created by clement.mathe on 06/06/2024.
//

#include "ReceptorApp.h"

ReceptorApp::ReceptorApp() {
    deviceManager = new ReceptorDeviceManager(loraInstance);
    deviceManager->init();
}

ReceptorApp::~ReceptorApp() {
    delete deviceManager;
}

void ReceptorApp::loop() {
    deviceManager->loop();
}