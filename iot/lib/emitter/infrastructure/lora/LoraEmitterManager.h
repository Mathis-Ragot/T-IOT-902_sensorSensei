//
// Created by clement.mathe on 06/06/2024.
//

#ifndef IOT_LORAEMITTERMANAGER_H
#define IOT_LORAEMITTERMANAGER_H

#include "infrastructure/CommunicationManager/LoRaCommunicationManager.h"
#include "LoRa.h"

class LoraEmitterManager : public LoRaCommunicationManager {
public:
    LoraEmitterManager()
            : LoRaCommunicationManager()  {}

    void setupLoRa() const override;
};


#endif //IOT_LORAEMITTERMANAGER_H
