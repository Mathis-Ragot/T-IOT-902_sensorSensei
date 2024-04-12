# Heltec Automation LoRa 32


## Description du Composant :
Le Heltec Automation LoRa 32 est un module de développement intégrant les fonctionnalités de communication sans fil LoRa et Bluetooth, ainsi qu'un microcontrôleur ESP32. Ce composant est conçu pour les applications IoT (Internet des objets) nécessitant une communication longue portée et une connectivité Bluetooth.

## Spécifications Techniques :

- Microcontrôleur : ESP32 dual-core Xtensa 32-bit LX6
- Fréquence du processeur : Jusqu'à 240 MHz
- Mémoire :
  - RAM : 520 Ko 
  - Flash : 4 Mo
- Interfaces :
  - LoRa (Long Range) : SX1276 LoRa transceiver
  - Bluetooth : Bluetooth 4.2 avec BLE (Bluetooth Low Energy)
  - Wi-Fi : 802.11 b/g/n
  - Interfaces UART, SPI, I2C, GPIO, ADC, DAC
- Alimentation :
  - Tension d'alimentation : 3.3V
  - Courant en veille : < 150 µA
- Dimensions : 51.2mm x 25.7mm x 8mm
- Température de fonctionnement : -40°C à +85°C

## Fonctionnalités Principales :

Communication sans fil longue portée via LoRa jusqu'à plusieurs kilomètres.
Connectivité Bluetooth pour la communication à courte portée et le contrôle à distance.
Intégration avec le microcontrôleur ESP32, offrant une puissance de calcul et une flexibilité pour les applications IoT.
Prise en charge du protocole LoRaWAN pour une connectivité IoT robuste et évolutive.
Capacité de fonctionner en tant que nœud de réseau ou en tant que passerelle pour d'autres dispositifs LoRa.
Prend en charge la programmation via l'environnement de développement Arduino IDE.

## Guide d'Utilisation :

- Étape 1 : Connectez le module Heltec LoRa 32 à votre ordinateur à l'aide d'un câble micro USB. 
- Étape 2 : Ouvrez l'environnement de développement.
- Étape 3 : Sélectionnez le type de carte "Heltec Automation LoRa 32" dans les paramètres de l'IDE.
- Étape 4 : Utilisez les bibliothèques disponibles pour développer votre application, en tenant compte des spécificités de la communication LoRa ou Bluetooth.
- Étape 5 : Téléversez votre code sur le module Heltec LoRa 32 et observez les résultats.
- Étape 6 : Pour la communication LoRa, assurez-vous de configurer les paramètres de fréquence, de puissance et de débit de données selon les besoins de votre application.

## Pinout :

![image](https://community.hiveeyes.org/uploads/default/eda042713108809e3511e822a1aa4e582ee70ebc)
