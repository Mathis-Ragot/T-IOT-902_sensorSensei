//
// Created by clement.mathe on 14/06/2024.
//

#ifndef IOT_DATAMANAGER_H
#define IOT_DATAMANAGER_H

#include <vector>
#include <cstdint>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <Arduino.h>
#include "../../receptor/domain/Measures.h"

class DataManager {
public:

    explicit DataManager(size_t queueSize);
    ~DataManager();

    bool enqueuePacket(const uint8_t *data, size_t length);
    bool dequeuePacket(std::vector<uint8_t> &packet);
//    std::vector<uint8_t> deserializePacket(const std::vector<uint8_t> &packet);
    measure::Measures measures;

private:
    QueueHandle_t packetQueue;
};



#endif //IOT_DATAMANAGER_H