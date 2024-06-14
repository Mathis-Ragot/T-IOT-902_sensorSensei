//
// Created by clement.mathe on 06/06/2024.
//

#ifndef IOT_LORARECEPTORMANAGER_H
#define IOT_LORARECEPTORMANAGER_H

#include "LoRaCommunicationManager.h"

class LoraReceptorManager : public LoRaCommunicationManager {

public:
    explicit LoraReceptorManager(LoRaClass &loraInstance, QueueHandle_t queue)
            : LoRaCommunicationManager(loraInstance,queue ) {}

    void setupLoRa() const override;
};


#endif //IOT_LORARECEPTORMANAGER_H
