//
// Created by nico on 06/06/24.
//

#include "WifiManager.h"

WifiManager::WifiManager(IotWifiClient *client) {
    this->client = std::make_shared<IotWifiClient*>(client);
}

WifiManager::WifiManager(const WifiManager &manager) {
    this->client = manager.client;
}

tl::optional<std::string> WifiManager::initialize() {
    if (!(*this->client)->connect(WIFI_SSID, WIFI_PASSWORD, WIFI_TIMEOUT)) {
        return tl::make_optional("Wifi connection timeout !!!");
    }
    return tl::nullopt;
}

WifiManager::~WifiManager() {
    (*this->client)->disconnect();
}

