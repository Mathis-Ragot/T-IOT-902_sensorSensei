//
// Created by clement.mathe on 06/06/2024.
//

#ifndef IOT_RECEPTORAPP_H
#define IOT_RECEPTORAPP_H

#include <Arduino.h>
#include "ReceptorDeviceManager.h"

#ifdef LORA_RECEPTOR
#include <heltec.h>
//extern LoRaClass &LoRa;
#endif

#ifdef LORA_EMITTER
#include <LoRa.h>
extern LoRaClass LoRa;
#endif

class ReceptorApp {
public:
    ReceptorApp();
    ~ReceptorApp();
    void loop();
private:
    ReceptorDeviceManager *deviceManager;
    LoRaClass loraInstance;
};
#endif //IOT_RECEPTORAPP_H
