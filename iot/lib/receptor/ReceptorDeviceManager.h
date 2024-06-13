//
// Created by clement.mathe on 06/06/2024.
//

#ifndef IOT_RECEPTORDEVICEMANAGER_H
#define IOT_RECEPTORDEVICEMANAGER_H

#include <vector>
#include <memory>
#include "LoRaCommunicationManager.h"
#include "DeviceInfos.h"
#include "infrastructure/lora/LoraReceptorManager.h"
#include "infrastructure/wifi/WifiManager.h"
#include "SensorApi.h"

class ReceptorDeviceManager {

public:
    DeviceInfos deviceInfo;
    explicit ReceptorDeviceManager(LoRaClass &loraInstance);
    ~ReceptorDeviceManager();
    void init() const;
    void loop() const;
    void communicateMeasures();
    void communicateInfos();
private:
    std::unique_ptr<LoRaCommunicationManager> communicationManager;
    WifiManager *wifiManager;
    SensorApi *api;
};


#endif //IOT_RECEPTORDEVICEMANAGER_H
