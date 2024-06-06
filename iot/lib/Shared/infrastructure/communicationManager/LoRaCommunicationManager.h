//
// Created by clement.mathe on 12/04/2024.
//

#ifndef T_IOT_902_SENSORSENSEI_COMMUNICATIONMANAGER_H
#define T_IOT_902_SENSORSENSEI_COMMUNICATIONMANAGER_H

#include "ICommunication.h"
#include "Arduino.h"
#include "LoRa.h"


class LoRaCommunicationManager : public communication::ICommunication {

public:
    LoRaCommunicationManager();
    virtual ~LoRaCommunicationManager() = default;

    void init() override;
    void connect() override;
    void send(const uint8_t* data, size_t  size) override;
    void receive() override;
    void reconnect() override;
    void close() override;

private:



protected:
    virtual void setupLoRa() const = 0;
    // Slave Select pin
    int resetPin;  // Reset pin
    int irqPin;    // Interrupt Request pin
    long frequency;  // Frequency channel
    int ssPin;
};


#endif //T_IOT_902_SENSORSENSEI_COMMUNICATIONMANAGER_H
