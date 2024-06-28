//
// Created by clement.mathe on 06/06/2024.
//

#include "LoraReceptorManager.h"

LoraReceptorManager::LoraReceptorManager(LoRaClass &loraInstance, DataManager &queueManager)
        : LoRaCommunicationManager(loraInstance), receiveTaskHandle(nullptr), dataQueueManager(queueManager) {}

LoraReceptorManager::~LoraReceptorManager() {
    if (receiveTaskHandle != nullptr) {
        vTaskDelete(receiveTaskHandle);
    }
}

void LoraReceptorManager::setupLoRa() const {

    if (!LoRa.begin(LORA_FREQUENCY, true)) {
        Serial.println("Erreur lors de l'initialisation de LoRa sur Heltec.");
    }

    LoRa.setTxPower(LORA_TX_POWER, PA_OUTPUT_PA_BOOST_PIN);
    LoRa.setSpreadingFactor(LORA_SPREADING_FACTOR);
    LoRa.setSignalBandwidth(LORA_BANDWIDTH);
    LoRa.setCodingRate4(LORA_CODING_RATE);
    LoRa.setPreambleLength(
            LORA_PREAMBLE_LENGTH); //séquence d'octets envoyée en tête de chaque paquet pour synchroniser le récepteur avec l'émetteur
    LoRa.setSyncWord(LORA_SYNC_WORD);
    LoRa.enableCrc();

    Serial.println("LoRa initialisé avec succès sur Heltec.");
}



void LoraReceptorManager::receiveTask(void *param) {
    auto *manager = static_cast<LoraReceptorManager *>(param);
    while (true) {
        int packetSize = manager->LoRa.parsePacket();
        if (packetSize) {
            std::vector<uint8_t> packet(packetSize);
            for (int i = 0; i < packetSize; ++i) {
                packet[i] = manager->LoRa.read();
            }
            manager->dataQueueManager.enqueuePacket(packet.data(), packet.size());
        }
        vTaskDelay(10 / portTICK_PERIOD_MS); // Réduisez le délai si nécessaire
    }
}

void LoraReceptorManager::connect() {
    xTaskCreate(&LoraReceptorManager::receiveTask, "LoRaReceiveTask", 4096, this, 1, &receiveTaskHandle);
    Serial.println("LoRa is setup and ready.");
}

void LoraReceptorManager::receive() {
    LoRaCommunicationManager::receive();
}
