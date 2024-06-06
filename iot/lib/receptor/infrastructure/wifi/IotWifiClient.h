#ifndef IOT_IOTWIFICLIENT_H
#define IOT_IOTWIFICLIENT_H

#include <string>

class IotWifiClient {
public:
    virtual bool restart() = 0;
    virtual bool connect(std::string ssid, std::string password, int max_delay) = 0;
    virtual bool disconnect() = 0;
};


#endif //IOT_IOTWIFICLIENT_H
