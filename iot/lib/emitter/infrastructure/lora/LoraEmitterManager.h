//
// Created by clement.mathe on 06/06/2024.
//

#ifndef IOT_LORAEMITTERMANAGER_H
#define IOT_LORAEMITTERMANAGER_H

//#include "infrastructure/CommunicationManager/LoRaCommunicationManager.h"
#include "../../Shared/src/infrastructure/CommunicationManager/LoRaCommunicationManager.h"


class LoraEmitterManager : public LoRaCommunicationManager {
public:
public:
    explicit LoraEmitterManager(LoRaClass &loraInstance)
            : LoRaCommunicationManager(loraInstance, LORA_SS_PIN, LORA_RESET_PIN, LORA_IRQ_PIN, LORA_FREQUENCY) {}


    void setupLoRa() const override;
};


#endif //IOT_LORAEMITTERMANAGER_H
