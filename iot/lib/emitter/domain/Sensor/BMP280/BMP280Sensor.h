//
// Created by clavi on 03/05/2024.
//

#include "../AbstractSensor.h"
#include "Adafruit_BMP280.h"

#ifndef IOT_BPM280SENSOR_H
#define IOT_BPM280SENSOR_H

namespace sensor {

    class BMP280Sensor : public AbstractSensor {

    public:
        explicit BMP280Sensor();

        void begin() override;

    protected:
        Adafruit_BMP280 bmp;

    private:
        Adafruit_BMP280::sensor_mode mode = Adafruit_BMP280::MODE_NORMAL;
        Adafruit_BMP280::sensor_sampling tempSampling = Adafruit_BMP280::SAMPLING_X1;
        Adafruit_BMP280::sensor_sampling pressSampling = Adafruit_BMP280::SAMPLING_X1;
        Adafruit_BMP280::sensor_filter filter = Adafruit_BMP280::FILTER_OFF;
        Adafruit_BMP280::standby_duration duration = Adafruit_BMP280::STANDBY_MS_1;

        void configureSensor();

    };

}

#endif //IOT_BPM280SENSOR_H
