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
#include "core/DataManager.h"

class ReceptorDeviceManager {

public:
    DeviceInfos deviceInfo;
    explicit ReceptorDeviceManager(LoRaClass &loraInstance);
    ~ReceptorDeviceManager();
    void init() const;
    void loop();
    void communicateMeasures();
    void communicateInfos();
private:
    LoRaCommunicationManager* communicationManager;
    WifiManager *wifiManager;
    SensorApi *api;

    DataManager queueManager;
    void processReceivedPacket(std::vector<uint8_t> &packet);



};


#endif //IOT_RECEPTORDEVICEMANAGER_H
