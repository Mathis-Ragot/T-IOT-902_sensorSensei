//
// Created by clement.mathe on 06/06/2024.
//

#include "LoraEmitterManager.h"

void LoraEmitterManager::setupLoRa() const {
    LoRa.setPins(ssPin, resetPin, irqPin);

    if (!LoRa.begin(frequency)) {
        Serial.println("Starting LoRa failed!");
        while (true);
    }
    LoRa.setTxPower(LORA_TX_POWER, PA_OUTPUT_PA_BOOST_PIN);
    LoRa.setSpreadingFactor(LORA_SPREADING_FACTOR);
    LoRa.setSignalBandwidth(LORA_BANDWIDTH);
    LoRa.setCodingRate4(LORA_CODING_RATE);
    LoRa.setPreambleLength(LORA_PREAMBLE_LENGTH);
    LoRa.setSyncWord(LORA_SYNC_WORD);
    LoRa.enableCrc();
}