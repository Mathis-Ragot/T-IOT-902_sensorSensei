//
// Created by clement.mathe on 12/04/2024.
//

#ifndef T_IOT_902_SENSORSENSEI_COMMUNICATIONMANAGER_H
#define T_IOT_902_SENSORSENSEI_COMMUNICATIONMANAGER_H

#include "ICommunication.h"
#include "Arduino.h"
#include "optional.hpp"
#include <vector>
#include <FreeRTOSConfig.h>
#include <freertos/queue.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#ifdef LORA_RECEPTOR
#include "heltec.h"
#endif

#ifdef LORA_EMITTER
#include <LoRa.h>
#endif


class LoRaCommunicationManager : public communication::ICommunication {

public:
    explicit LoRaCommunicationManager(LoRaClass &loraInstance, tl::optional<QueueHandle_t> queue = tl::nullopt) :
            LoRa(loraInstance), packetQueue(queue), receiveTaskHandle(nullptr), ssPin(LORA_SS_PIN), resetPin(LORA_RESET_PIN), irqPin(LORA_IRQ_PIN), frequency(LORA_FREQUENCY) {};

    virtual ~LoRaCommunicationManager();

    void init() override;
    void connect() override;
    void send(const uint8_t* data, size_t  size) override;
    void receive() override;
    void reconnect() override;
    void close() override;

protected:

    LoRaClass &LoRa;
    virtual void setupLoRa() const = 0;
    // Slave Select pin
    int resetPin;  // Reset pin
    int irqPin;    // Interrupt Request pin
    long frequency;  // Frequency channel
    int ssPin;

private:
    tl::optional<QueueHandle_t> packetQueue;
    TaskHandle_t receiveTaskHandle{};
    void enqueuePacket(const uint8_t* data, size_t length) override;
    static void receiveTask(void *param);
};

#endif //T_IOT_902_SENSORSENSEI_COMMUNICATIONMANAGER_H
