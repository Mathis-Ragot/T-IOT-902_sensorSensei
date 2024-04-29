
#include "App.h"
#include "board/boards.h"

using namespace std;

EmitterDeviceManager *deviceManager;

App::App() {


    initBoard();
    delay(1500);

//    Serial.begin(MONITOR_SPEED);
//    delay(1000);

    deviceManager = new EmitterDeviceManager();
    deviceManager->init();

}

App::~App() {
    delete deviceManager;
}

void App::loop() {

deviceManager->loop();
}