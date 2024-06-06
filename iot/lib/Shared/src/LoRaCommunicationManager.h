//
// Created by clement.mathe on 12/04/2024.
//

#ifndef T_IOT_902_SENSORSENSEI_COMMUNICATIONMANAGER_H
#define T_IOT_902_SENSORSENSEI_COMMUNICATIONMANAGER_H

#include <vector>
#include "ICommunication.h"
#include "Arduino.h"
#include "IPacketObserver.h"

#ifdef LORA_RECEPTOR
#include "heltec.h"
#endif

#ifdef LORA_EMITTER
#include <LoRa.h>
#endif


class LoRaCommunicationManager : public communication::ICommunication {

public:
    LoRaCommunicationManager(LoRaClass &loraInstance, int ssPin, int resetPin, int irqPin, long frequency);

    virtual ~LoRaCommunicationManager() = default;

    void init() override;
    void connect() override;
    void send(const uint8_t* data, size_t  size) override;
    void receive() override;
    void reconnect() override;
    void close() override;

    void addObserver(IPacketObserver *observer);
    void removeObserver(IPacketObserver *observer);

protected:

    LoRaClass &LoRa;
    virtual void setupLoRa() const = 0;
    // Slave Select pin
    int resetPin;  // Reset pin
    int irqPin;    // Interrupt Request pin
    long frequency;  // Frequency channel
    int ssPin;

private:
    std::vector<IPacketObserver*> observers;
    void notifyObservers(const uint8_t *data, size_t length);
};



#endif //T_IOT_902_SENSORSENSEI_COMMUNICATIONMANAGER_H
