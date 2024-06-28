//
// Created by clement.mathe on 06/06/2024.
//

#ifndef IOT_LORARECEPTORMANAGER_H
#define IOT_LORARECEPTORMANAGER_H

#include "LoRaCommunicationManager.h"
#include "core/DataManager.h"

class LoraReceptorManager : public LoRaCommunicationManager {

public:
    LoraReceptorManager(LoRaClass &loraInstance, DataManager &dataQueueManager);
    ~LoraReceptorManager() override;

    void setupLoRa() const override;
    void connect() override;
    void receive() override;

private:
    static void receiveTask(void *param);
    DataManager &dataQueueManager;
    TaskHandle_t receiveTaskHandle;
};


#endif //IOT_LORARECEPTORMANAGER_H
