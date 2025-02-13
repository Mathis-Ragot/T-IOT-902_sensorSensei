//
// Created by clement.mathe on 06/06/2024.
//

#ifndef IOT_LORAEMITTERMANAGER_H
#define IOT_LORAEMITTERMANAGER_H

#include "LoRaCommunicationManager.h"

class LoraEmitterManager : public LoRaCommunicationManager {
public:
public:
    explicit LoraEmitterManager(LoRaClass &loraInstance)
            : LoRaCommunicationManager(loraInstance) {}


    void setupLoRa() const override;
};


#endif //IOT_LORAEMITTERMANAGER_H
