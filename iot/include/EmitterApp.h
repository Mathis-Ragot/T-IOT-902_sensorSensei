#ifndef ARGAMES_IOT_APP
#define ARGAMES_IOT_APP


#include <iostream>
#include "EmitterDeviceManager.h"
#include "Arduino.h"

#ifdef LORA_RECEPTOR
#include <heltec.h>
//extern LoRaClass &LoRa;
#endif

#ifdef LORA_EMITTER
#include <LoRa.h>
extern LoRaClass LoRa;
#endif


class EmitterApp {
public:
    EmitterApp();
    ~EmitterApp();
    void loop();
};

#endif //ARGAMES_IOT_APP