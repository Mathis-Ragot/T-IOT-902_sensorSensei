#ifndef ARDUINO_WIFI_CLIENT_H
#define ARDUINO_WIFI_CLIENT_H

#include "IotWifiClient.h"

#define WIFI_DELAY_COUNT 500

class ArduinoWifiClient : public IotWifiClient {
public:
    bool connect(std::string ssid, std::string password, int max_delay) override;
    bool disconnect() override;
    bool restart() override;
};

#endif