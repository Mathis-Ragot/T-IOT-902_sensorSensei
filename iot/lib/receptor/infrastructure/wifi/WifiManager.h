#ifndef IOT_WIFIMANAGER_H
#define IOT_WIFIMANAGER_H

#include <memory>
#include "IotWifiClient.h"
#include "optional.hpp"

class WifiManager {
public:
    explicit WifiManager(IotWifiClient *client);
    WifiManager(const WifiManager &manager);
    ~WifiManager();
    tl::optional<std::string> initialize();
private:
    std::shared_ptr<IotWifiClient*> client;
};


#endif //IOT_WIFIMANAGER_H
