//
// Created by clement.mathe on 06/06/2024.
//

#ifndef IOT_LORARECEPTORMANAGER_H
#define IOT_LORARECEPTORMANAGER_H

#include "LoRaCommunicationManager.h"

class LoraReceptorManager : public LoRaCommunicationManager {

public:
    explicit LoraReceptorManager(LoRaClass &loraInstance)
            : LoRaCommunicationManager(loraInstance, LORA_SS_PIN, LORA_RESET_PIN, LORA_IRQ_PIN, LORA_FREQUENCY) {}

    void setupLoRa() const override;
};


#endif //IOT_LORARECEPTORMANAGER_H
