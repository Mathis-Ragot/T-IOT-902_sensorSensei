//
// Created by clavi on 03/05/2024.
//
#include "TemperatureSensor.h"

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

    if (measure > 4095) {
        measure = 4095;  // Cap the value to fit within 12 bits
    }

    Serial.print("Temperature: ");
    Serial.println(measure);

    return static_cast<uint16_t>(measure);
}