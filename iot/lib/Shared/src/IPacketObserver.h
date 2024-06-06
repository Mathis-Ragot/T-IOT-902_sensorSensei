//
// Created by clement.mathe on 06/06/2024.
//

#ifndef IOT_IPACKETOBSERVER_H
#define IOT_IPACKETOBSERVER_H

#include <cstdint>
#include <cstdio>

class IPacketObserver {
public:
    virtual void onPacketReceived(const uint8_t *data, size_t length) = 0;
};


#endif //IOT_IPACKETOBSERVER_H
