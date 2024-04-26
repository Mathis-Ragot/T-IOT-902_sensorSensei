//
// Created by clement.mathe on 12/04/2024.
//

#ifndef T_IOT_902_SENSORSENSEI_COMMUNICATIONMANAGER_H
#define T_IOT_902_SENSORSENSEI_COMMUNICATIONMANAGER_H

#include "ICommunication.h"
#include "Arduino.h"
#include <LoRa.h>


class LoRaCommunicationManager : public ICommunication {

public:
    LoRaCommunicationManager();
    virtual ~LoRaCommunicationManager() = default;

    void init() override;
    void connect() override;
    void send(const uint8_t* data) override;
    void receive() override;
    void reconnect() override;
    void close() override;

private:

    int ssPin;     // Slave Select pin
    int resetPin;  // Reset pin
    int irqPin;    // Interrupt Request pin
    long frequency;  // Frequency channel


    void setupLoRa() const;
};


#endif //T_IOT_902_SENSORSENSEI_COMMUNICATIONMANAGER_H
