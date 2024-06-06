//
// Created by clement.mathe on 06/06/2024.
//

#ifndef IOT_RECEPTORAPP_H
#define IOT_RECEPTORAPP_H

#include <Arduino.h>
#include "ReceptorDeviceManager.h"
#include "infrastructure/wifi/WifiManager.h"
#include "SensorApi.h"

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
    WifiManager *wifiManager;
    SensorApi *api;
};
#endif //IOT_RECEPTORAPP_H
