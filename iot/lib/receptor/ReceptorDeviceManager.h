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
    explicit ReceptorDeviceManager(LoRaClass &loraInstance);
    ~ReceptorDeviceManager();
    void init() const;
    void loop();
    void communicateMeasures();
    void communicateInfos();
private:
    LoRaCommunicationManager* communicationManager;
    WifiManager *wifiManager;
    SensorApi *api;

    DataManager dataManager;
    void processReceivedPacket(std::vector<uint8_t> &packet);



};


#endif //IOT_RECEPTORDEVICEMANAGER_H
