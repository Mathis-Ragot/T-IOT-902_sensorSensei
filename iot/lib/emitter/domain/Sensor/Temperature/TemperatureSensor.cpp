//
// Created by clavi on 03/05/2024.
//
#include "TemperatureSensor.h"
#include "domain/Sensor/Sensors.h"

sensor::TemperatureSensor::TemperatureSensor() : BMP280Sensor() {
    this->dataBitLength = TEMP_SENSOR_DATA_BIT_LENGTH;
    this->infos = SensorInfos(
            TEMP_SENSOR_ID,
            TEMP_SENSOR_REF,
            std::vector<SensorType>{SensorInfos::stringToSensorType(TEMP_SENSOR_TYPE)}
    );
}

float sensor::TemperatureSensor::getMeasure() {
    return this->bmp.readTemperature();
}

uint16_t sensor::TemperatureSensor::getSerializedMeasure() {
    float measure = getMeasure();

    if (measure > MaxMeasureSize) {
        measure = MaxMeasureSize;  // Cap the value to fit within 12 bits
    }

    #ifdef TEMP_SENSOR_DEBUG
        Serial.print("Temperature: ");
        Serial.println(measure);
    #endif
    return static_cast<uint16_t>(measure);
}