//
// Created by clement.mathe on 06/06/2024.
//

#ifndef IOT_RECEPTORDEVICEMANAGER_H
#define IOT_RECEPTORDEVICEMANAGER_H


#include <vector>
#include <memory>
//#include "infrastructure/CommunicationManager/LoRaCommunicationManager.h"
#include "LoRaCommunicationManager.h"
#include "DeviceInfos.h"
#include "infrastructure/lora/LoraReceptorManager.h"

class ReceptorDeviceManager {

private:
    std::unique_ptr<LoRaCommunicationManager> communicationManager;

public:
    DeviceInfos deviceInfo;

    explicit ReceptorDeviceManager(LoRaClass &loraInstance);

    void init() const;

    void loop() const;

    void communicateMeasures();

    void communicateInfos();
};


#endif //IOT_RECEPTORDEVICEMANAGER_H
