//
// Created by clement.mathe on 12/04/2024.
//

#ifndef T_IOT_902_SENSORSENSEI_ICOMMUNICATION_H
#define T_IOT_902_SENSORSENSEI_ICOMMUNICATION_H

#include <cstdint>
#include <cstdio>

namespace communication {

    class ICommunication {
    public:
        virtual void init() = 0;

        virtual void connect() = 0;

        virtual void send(const uint8_t *data, size_t size) = 0;

        virtual void receive() = 0;

        virtual void reconnect() = 0;

        virtual void close() = 0;

        virtual void enqueuePacket(const uint8_t* data, size_t length) = 0;


    };
}
#endif //T_IOT_902_SENSORSENSEI_ICOMMUNICATION_H
