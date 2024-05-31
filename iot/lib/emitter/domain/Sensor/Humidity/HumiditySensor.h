#include "Arduino.h"
#include "domain/Sensor/ISensor.h"
#include "domain/SensorInfos/SensorInfos.h"
#include "domain/Sensor/AbstractSensor.h"
#include <string>
#include <iostream>
#include "DHT.h"

#ifndef IOT_HUMIDITYSENSOR_H
#define IOT_HUMIDITYSENSOR_H

namespace sensor
{

    class HumiditySensor : public AbstractSensor
    {

    public:
        explicit HumiditySensor();

        void begin() override;

        float getMeasure() override;

        uint16_t getSerializedMeasure() override;

        ~HumiditySensor();

    protected:
        DHT *dht;

    private:
        int dhtPin = HUMIDITY_MEASURE_PIN;
        uint8_t dht11 = DHT11;
    };

}
#endif // IOT_HUMIDITYSENSOR_H
