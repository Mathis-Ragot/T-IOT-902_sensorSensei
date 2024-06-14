#include <vector>
#include "LoRaCommunicationManager.h"

LoRaCommunicationManager::~LoRaCommunicationManager() {
    if (receiveTaskHandle != nullptr) {
        vTaskDelete(receiveTaskHandle);
    }
}

void LoRaCommunicationManager::init() {
    setupLoRa();
}


void LoRaCommunicationManager::connect() {
    xTaskCreate(&LoRaCommunicationManager::receiveTask, "LoRaReceiveTask", 4096, this, 1, &receiveTaskHandle);
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

void LoRaCommunicationManager::enqueuePacket(const uint8_t *data, size_t length) {
    auto* packet = new std::vector<uint8_t>(data, data + length);
    if(packetQueue.has_value()) {
        if (xQueueSendToBack(packetQueue.value(), &packet, pdMS_TO_TICKS(1000)) != pdPASS) {
            Serial.println("Failed to send packet to queue");
            delete packet; // Libère la mémoire si l'envoi échoue
        }
    }
}

void LoRaCommunicationManager::receiveTask(void *param) {
    Serial.println("Starting receive task");
    auto *manager = static_cast<LoRaCommunicationManager *>(param);
    while (true) {
        int packetSize = manager->LoRa.parsePacket();
        if (packetSize) {
            std::vector<uint8_t> packet(packetSize);
            for (int i = 0; i < packetSize; ++i) {
                packet[i] = manager->LoRa.read();
            }

            manager->enqueuePacket(packet.data(), packet.size());
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

