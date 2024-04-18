
#include "App.h"

using namespace std;

EmitterDeviceManager *deviceManager;

App::App() {

    Serial.begin(9600);
    delay(1000);
    deviceManager = new EmitterDeviceManager();
}

App::~App() {
    delete deviceManager;
}

void App::loop() {

    deviceManager->init();
    Serial.print("DeviceManager init");
}