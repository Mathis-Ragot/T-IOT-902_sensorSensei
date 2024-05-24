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
    float temperature = this->bmp.readTemperature();

    Serial.println("Temperature: ");
    Serial.println(temperature);

    return temperature;
}

uint16_t sensor::TemperatureSensor::getSerializedMeasure() {
    float measure = getMeasure();
    int measureInt = static_cast<int>(std::round(measure));

    if (measureInt > 4095) {
        measureInt = 4095;  // Cap the value to fit within 12 bits
    }

    return static_cast<uint16_t>(measureInt);
}