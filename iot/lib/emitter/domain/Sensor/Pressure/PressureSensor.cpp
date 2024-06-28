//
// Created by clavi on 03/05/2024.
//
#include "PressureSensor.h"
#include "domain/Sensor/Sensors.h"

sensor::PressureSensor::PressureSensor() : BMP280Sensor() {
    this->dataBitLength = TEMP_SENSOR_DATA_BIT_LENGTH;
    this->infos = SensorInfos(
            PRESSURE_SENSOR_ID,
            PRESSURE_SENSOR_REF,
            std::vector<SensorType>{SensorInfos::stringToSensorType(PRESSURE_SENSOR_TYPE)}
    );
}

float sensor::PressureSensor::getMeasure() {
    auto measure = this->bmp.readPressure();
#ifdef PRESSURE_SENSOR_DEBUG
    Serial.print("Pressure  ");
    Serial.print(measure);
    Serial.println(" Pa");
#endif
    return measure;
}

uint16_t sensor::PressureSensor::getSerializedMeasure() {
    auto measure = static_cast<uint16_t>(getMeasure()/100);

    if (measure > MaxMeasureSize) {
        measure = MaxMeasureSize;  // Cap the value to fit within 12 bits
    }
#ifdef PRESSURE_SENSOR_DEBUG
    Serial.print("Pressure serialized: ");
    Serial.print(measure);
    Serial.println();
#endif

    return measure;
}