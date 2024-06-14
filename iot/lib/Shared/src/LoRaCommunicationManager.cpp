#include <vector>
#include "LoRaCommunicationManager.h"



void LoRaCommunicationManager::init() {
    setupLoRa();
}


void LoRaCommunicationManager::connect() {
    Serial.println("LoRa is setup and ready.");
}

void LoRaCommunicationManager::send(const uint8_t *data, size_t length) {
    LoRa.beginPacket();
    LoRa.write(data, length);
    LoRa.endPacket();
    Serial.println("Packet sent");
}

void LoRaCommunicationManager::receive() {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {

        std::vector<uint8_t> packet(packetSize);
        for (int i = 0; i < packetSize; ++i) {
            packet[i] = LoRa.read();
        }
        Serial.print("Received packet: ");
        for (const auto &byte : packet) {
            Serial.print(byte, HEX);
            Serial.print(" ");
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




