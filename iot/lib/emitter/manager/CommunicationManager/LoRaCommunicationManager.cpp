//
// Created by clement.mathe on 12/04/2024.
//

#include "LoRaCommunicationManager.h"

LoRaCommunicationManager::LoRaCommunicationManager() : ssPin(LORA_SS_PIN), resetPin(LORA_RESET_PIN),irqPin(LORA_IRQ_PIN),
                                                       frequency(LORA_FREQUENCY) {
}

void LoRaCommunicationManager::init() {
    setupLoRa();
}

void LoRaCommunicationManager::connect() {
    // Typically, there's no "connect" method for LoRa, it's a direct send and receive setup.
    // This method might be used to reset or check status.
    Serial.println("LoRa is setup and ready.");
}

void LoRaCommunicationManager::send(const uint8_t *data) {
    LoRa.beginPacket();
    while (*data) {
        LoRa.write(*data++);
    }
    LoRa.endPacket();
    Serial.println("Packet sent");
}

void LoRaCommunicationManager::receive() {
    // This implementation must be called periodically to check for incoming packets
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        Serial.print("Received packet: ");
        while (LoRa.available()) {
            Serial.print((char) LoRa.read());
        }
        Serial.println();
    }
}

void LoRaCommunicationManager::reconnect() {
    close();
    init();
}

void LoRaCommunicationManager::close() {
    LoRa.end();
}

void LoRaCommunicationManager::setupLoRa() const {
    LoRa.setPins(ssPin, resetPin, irqPin);

    if (!LoRa.begin(frequency)) {
        Serial.println("Starting LoRa failed!");
        while (true);
    }
}


