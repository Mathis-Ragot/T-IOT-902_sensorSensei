#include "LoRaCommunicationManager.h"

LoRaCommunicationManager::LoRaCommunicationManager(LoRaClass &loraInstance, int ssPin, int resetPin, int irqPin, long frequency)
        : LoRa(loraInstance), ssPin(ssPin), resetPin(resetPin), irqPin(irqPin), frequency(frequency) {}

void LoRaCommunicationManager::init() {
    setupLoRa();
}

void LoRaCommunicationManager::connect() {
    Serial.println("LoRa is setup and ready.");
}

void LoRaCommunicationManager::send(const uint8_t* data, size_t length) {
    LoRa.beginPacket();
    LoRa.write(data, length);
    LoRa.endPacket();
    Serial.println("Packet sent");
}

void LoRaCommunicationManager::receive() {
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
