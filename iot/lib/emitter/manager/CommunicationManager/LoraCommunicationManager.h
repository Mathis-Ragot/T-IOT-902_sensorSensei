//
// Created by clement.mathe on 12/04/2024.
//

#ifndef T_IOT_902_SENSORSENSEI_COMMUNICATIONMANAGER_H
#define T_IOT_902_SENSORSENSEI_COMMUNICATIONMANAGER_H

#include "ICommunication.h"

class LoraCommunicationManager : public ICommunication {

public:
    LoraCommunicationManager();
    void init() override;
    void send(const uint8_t* data) override;
    void close() override;
    void receive() override;
    void connect() override;
    void reconnect() override;
};


#endif //T_IOT_902_SENSORSENSEI_COMMUNICATIONMANAGER_H
