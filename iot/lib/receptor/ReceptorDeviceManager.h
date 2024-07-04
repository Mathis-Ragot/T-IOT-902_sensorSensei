//
// Created by clement.mathe on 06/06/2024.
//

#ifndef IOT_RECEPTORDEVICEMANAGER_H
#define IOT_RECEPTORDEVICEMANAGER_H

#include <vector>
#include <memory>
#include "LoRaCommunicationManager.h"
#include "DeviceInfos.h"
#include "infrastructure/lora/LoraReceptorManager.h"
#include "infrastructure/wifi/WifiManager.h"
#include "MyHttpClient.h"
#include "infrastructure/wifi/ArduinoWifiClient.h"
#include "SensorApi.h"
#include "core/DataManager.h"
#include "domain/DustMeasure.h"
#include "domain/SoundMeasure.h"
#include "domain/TemperatureMeasure.h"
#include "domain/PressureMeasure.h"
#include "domain/HumidityMeasure.h"
#include <Arduino.h>


class ReceptorDeviceManager {

public:
    DeviceInfos deviceInfo;

    /**
     * @brief Constructor of the ReceptorDeviceManager class.
     * Initializes the communication, API, and WiFi managers, and adds the measures to the DataManager.
     *
     * @param loraInstance Reference to an instance of LoRaClass used for LoRa communication.
     */
    explicit ReceptorDeviceManager(LoRaClass &loraInstance);
    ~ReceptorDeviceManager();

    /**
     * @brief Initialization method for the ReceptorDeviceManager.
     * Initializes the Heltec display, communication manager, and WiFi manager.
     */
    void init() const;
    /**
     * @brief Main loop method for the ReceptorDeviceManager.
     * Checks and processes received packets.
     */
    void loop();
    /**
     * @brief Method to communicate measures.
     * Currently not implemented.
     */
    void communicateMeasures();
    /**
    * @brief Method to communicate information.
    * Currently not implemented.
    */
    void communicateInfos();
private:
    LoRaCommunicationManager* communicationManager;
    WifiManager *wifiManager;
    SensorApi *api;

    DataManager dataManager;

    /**
     * @brief Processes a received packet.
     * Verifies the packet's authenticity, deserializes the measures, and displays them on the Heltec screen.
     *
     * @param packet The received packet to process.
     */
    void processReceivedPacket(std::vector<uint8_t> &packet);



};


#endif //IOT_RECEPTORDEVICEMANAGER_H
