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
        notifyObservers(packet.data(), packet.size());
    }
}

void LoRaCommunicationManager::reconnect() {
    close();
    init();
}

void LoRaCommunicationManager::close() {
    LoRa.end();
}

void LoRaCommunicationManager::addObserver(IPacketObserver *observer) {
    observers.push_back(observer);
}

void LoRaCommunicationManager::removeObserver(IPacketObserver *observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void LoRaCommunicationManager::notifyObservers(const uint8_t *data, size_t length) {
    for (auto *observer : observers) {
        observer->onPacketReceived(data, length);
    }
}
