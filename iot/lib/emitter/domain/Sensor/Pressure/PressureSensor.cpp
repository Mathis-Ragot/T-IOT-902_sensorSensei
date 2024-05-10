//
// Created by clavi on 03/05/2024.
//
#include "PressureSensor.h"

sensor::PressureSensor::PressureSensor() : BMP280Sensor() {
    this->dataBitLength = TEMP_SENSOR_DATA_BIT_LENGTH;
    this->infos = SensorInfos(
            PRESSURE_SENSOR_ID,
            PRESSURE_SENSOR_REF,
            std::vector<SensorType>{SensorInfos::stringToSensorType(PRESSURE_SENSOR_TYPE)}
    );
}

float sensor::PressureSensor::getMeasure() {
    float pressure = this->bmp.readPressure();

    Serial.println("Pressure: ");
    Serial.println(pressure / 100.0f);

    return pressure;
}

uint16_t sensor::PressureSensor::getSerializedMeasure() {
    float measure = getMeasure();
    int measureInt = static_cast<int>(std::round(measure));

    if (measureInt > 4095) {
        measureInt = 4095;  // Cap the value to fit within 12 bits
    }

    return static_cast<uint16_t>(measureInt);
}