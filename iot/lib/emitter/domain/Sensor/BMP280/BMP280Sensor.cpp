//
// Created by clavi on 03/05/2024.
//

#include "BMP280Sensor.h"

sensor::BMP280Sensor::BMP280Sensor() : AbstractSensor(){
    // It gives the same address for all Adafruit_BMP280 instances
    Adafruit_BMP280 bmp = Adafruit_BMP280();
    this->bmp = bmp;
}

void sensor::BMP280Sensor::begin() {
    unsigned status;
    status = bmp.begin(address);

    if (!status) {
        Serial.println(F("Could not find a valid BMP280 sensor, check wiring or try a different address!"));
        Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(), 16);
        Serial.print("\tID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("\tID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("\tID of 0x60 represents a BME 280.\n");
        Serial.print("\tID of 0x61 represents a BME 680.\n");
        return;
    }

    configureSensor();
}

void sensor::BMP280Sensor::configureSensor() {
    bmp.setSampling(
        mode,
        tempSampling,
        pressSampling,
        filter,
        duration
    );
}
