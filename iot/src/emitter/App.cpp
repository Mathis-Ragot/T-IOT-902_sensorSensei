
#include "App.h"

using namespace std;

EmitterDeviceManager *deviceManager;

App::App() {

    Serial.begin(115200);
    delay(1000);
    deviceManager = new EmitterDeviceManager();
    deviceManager->init();

}

App::~App() {
    delete deviceManager;
}

void App::loop() {

deviceManager->loop();
}