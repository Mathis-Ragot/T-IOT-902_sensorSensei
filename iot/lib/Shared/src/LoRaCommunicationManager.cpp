#include "LoRaCommunicationManager.h"

//LoRaCommunicationManager::LoRaCommunicationManager(LoRaClass &loraInstance, QueueHandle_t queue)
//        : LoRa(loraInstance), packetQueue(queue),  ssPin(LORA_SS_PIN), resetPin(LORA_RESET_PIN), irqPin(LORA_IRQ_PIN), frequency(LORA_FREQUENCY)  {}


LoRaCommunicationManager::~LoRaCommunicationManager()  {
    if (receiveTaskHandle != nullptr) {
        vTaskDelete(receiveTaskHandle);
    }
}

void LoRaCommunicationManager::init() {
    setupLoRa();
    xTaskCreate(&LoRaCommunicationManager::receiveTask, "LoRaReceiveTask", 4096, this, 1, &receiveTaskHandle);

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

void LoRaCommunicationManager::enqueuePacket(const uint8_t* data, size_t length) {
    std::vector<uint8_t> packet(data, data + length);
    if (xQueueSend(packetQueue, &packet, portMAX_DELAY) != pdPASS) {
        Serial.println("Failed to enqueue packet");
    }
}

void LoRaCommunicationManager::receiveTask(void *param) {
    auto *manager = static_cast<LoRaCommunicationManager *>(param);
    while (true) {
        int packetSize = manager->LoRa.parsePacket();
        const size_t MAX_PACKET_SIZE = 256;

        if (packetSize) {
            std::vector<uint8_t> packet;
            packet.reserve(packetSize);

            for (int i = 0; i < packetSize; ++i) {
                packet[i] = manager->LoRa.read();
            }
            manager->enqueuePacket(packet.data(), packet.size());

            Serial.print("Received packet: ");
            for (const auto &byte: packet) {
                Serial.print(byte, HEX);
                Serial.print(" ");
            }
            Serial.println();
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
