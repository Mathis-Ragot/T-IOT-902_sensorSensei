//
// Created by clavi on 03/05/2024.
//
#include "PressureSensor.h"
#include "../Sensors.h"

sensor::PressureSensor::PressureSensor() : BMP280Sensor() {
    this->dataBitLength = TEMP_SENSOR_DATA_BIT_LENGTH;
    this->infos = SensorInfos(
            PRESSURE_SENSOR_ID,
            PRESSURE_SENSOR_REF,
            std::vector<SensorType>{SensorInfos::stringToSensorType(PRESSURE_SENSOR_TYPE)}
    );
}

float sensor::PressureSensor::getMeasure() {
    return this->bmp.readPressure();
}

uint16_t sensor::PressureSensor::getSerializedMeasure() {
    float measure = getMeasure();

    if (measure > MaxMeasureSize) {
        measure = MaxMeasureSize;  // Cap the value to fit within 12 bits
    }

    #ifdef PRESSURE_SENSOR_DEBUG
        Serial.print("Pressure: ");
        Serial.println(measure / 100.0f);
    #endif

    return static_cast<uint16_t>(measure);
}