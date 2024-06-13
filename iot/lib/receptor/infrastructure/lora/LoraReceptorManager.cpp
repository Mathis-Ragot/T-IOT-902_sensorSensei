//
// Created by clement.mathe on 06/06/2024.
//

#include "LoraReceptorManager.h"


void LoraReceptorManager::setupLoRa() const {

    if (!LoRa.begin(LORA_FREQUENCY, true)) {
        Serial.println("Erreur lors de l'initialisation de LoRa sur Heltec.");
        while (1);
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