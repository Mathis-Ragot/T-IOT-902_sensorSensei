//
// Created by clement.mathe on 14/06/2024.
//

#include "DataManager.h"

DataManager::DataManager(size_t queueSize) {
    packetQueue = xQueueCreate(queueSize, sizeof(std::vector<uint8_t>*));
    measures = measure::Measures();
}

DataManager::~DataManager() {
    if (packetQueue != nullptr) {
        vQueueDelete(packetQueue);
    }
}

bool DataManager::enqueuePacket(const uint8_t *data, size_t length) {
    auto* packet = new std::vector<uint8_t>(data, data + length);
    const TickType_t xTicksToWait = pdMS_TO_TICKS(1000); // Attente de 1s

    if (xQueueSendToBack(packetQueue, &packet, xTicksToWait) != pdPASS) {
        Serial.println("Failed to send packet to queue");
        delete packet; // Libère la mémoire si l'envoi échoue
        return false;
    } else {
        Serial.println("Packet enqueued");
        return true;
    }
}

bool DataManager::dequeuePacket(std::vector<uint8_t> &packet) {

    if(WiFi.isConnected()) {
        std::vector<uint8_t> *receivedPacket;
        if (xQueueReceive(packetQueue, &receivedPacket, portMAX_DELAY) == pdPASS) {
            packet = *receivedPacket;
            delete receivedPacket; // Libère la mémoire après traitement
            return true;
        }
    }
    return false;
}

//std::vector<uint8_t> DataManager::deserializePacket(const std::vector<uint8_t> &packet) {
//    std::vector<uint8_t> deserializedData;
//    if (packet.empty()) return deserializedData;
//
//    size_t totalLength = packet[0];
//    size_t bitIndex = 0;
//
//    for (size_t i = 1; i < packet.size(); ++i) {
//        uint8_t byte = packet[i];
//        for (size_t j = 0; j < 8 && bitIndex < totalLength; ++j, ++bitIndex) {
//            bool bit = (byte >> j) & 1;
//            deserializedData.push_back(bit);
//        }
//    }
//    return deserializedData;
//}
