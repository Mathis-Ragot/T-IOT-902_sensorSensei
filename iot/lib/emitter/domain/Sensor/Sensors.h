//
// Created by clement.mathe on 19/04/2024.
//

#ifndef IOT_SENSORS_H
#define IOT_SENSORS_H

#include <cstdint>
#include "AbstractSensor.h"
#include "shared_mutex"
#include <vector>
#include <memory>
#include <Arduino.h>

constexpr uint16_t MaxMeasureSize = 4095;

using namespace sensor;

class Sensors {
public:

    Sensors() = default;

    void addSensor(std::shared_ptr<AbstractSensor> sensor);

    std::vector<uint8_t> getSerializedMeasuresAsBytes();
    uint16_t deserializeMeasureFromBytes(const std::vector<uint8_t>& bytes, uint8_t dataBitLength);

    void getMeasures();

    void begin();

private:
    uint8_t serialize();

    std::vector<std::shared_ptr<AbstractSensor>> sensors;

};


#endif //IOT_SENSORS_H
