
#include "EmitterApp.h"
#include "board/boards.h"



using namespace std;

EmitterDeviceManager *deviceManager;

EmitterApp::EmitterApp() {

    initBoard();
    delay(1500);
    deviceManager = new EmitterDeviceManager(LoRa);

    deviceManager->init();
}

EmitterApp::~EmitterApp() {
    delete deviceManager;
}

void EmitterApp::loop() {
    deviceManager->loop();
}