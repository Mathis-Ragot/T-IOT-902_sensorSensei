
#include "App.h"

using namespace std;

DeviceManager *deviceManager;

App::App() {

    Serial.begin(9600);
    delay(1000);

    deviceManager = new DeviceManager();

}

void App::loop() {

}