//
// Created by clement.mathe on 06/06/2024.
//

#ifndef IOT_RECEPTORDEVICEMANAGER_H
#define IOT_RECEPTORDEVICEMANAGER_H

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <vector>
#include <memory>
#include "LoRaCommunicationManager.h"
#include "DeviceInfos.h"
#include "infrastructure/wifi/WifiManager.h"
#include "SensorApi.h"
#include "infrastructure/lora/LoraReceptorManager.h"
#include "MyHttpClient.h"
#include "infrastructure/wifi/ArduinoWifiClient.h"
#include "ExampleObserverReceptor.h"

class ReceptorDeviceManager {

public:
    DeviceInfos deviceInfo;
    explicit ReceptorDeviceManager(LoRaClass &loraInstance);
    ~ReceptorDeviceManager();
    void init();
    void loop() const;
    void communicateMeasures();
    void communicateInfos();
private:
    LoRaCommunicationManager* communicationManager;
    WifiManager *wifiManager;
    SensorApi *api;
    QueueHandle_t packetQueue;

};


#endif //IOT_RECEPTORDEVICEMANAGER_H
