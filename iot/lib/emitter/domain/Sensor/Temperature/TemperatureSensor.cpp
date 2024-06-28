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

    float measure = this->bmp.readTemperature();

#ifdef TEMP_SENSOR_DEBUG
    Serial.print("Temperature: ");
    Serial.print(celsiusToFahrenheit(measure));
    Serial.println("°F ");
#endif

    return celsiusToFahrenheit(measure);
}

float sensor::TemperatureSensor::celsiusToFahrenheit(float celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

uint16_t sensor::TemperatureSensor::getSerializedMeasure() {
    float measure = getMeasure();

    if (measure > MaxMeasureSize) {
        measure = MaxMeasureSize;  // Cap the value to fit within 12 bits
    }
    auto measureInt = static_cast<uint16_t>(std::round(measure * 10));

#ifdef TEMP_SENSOR_DEBUG
    Serial.print("Temperature serialized: ");
    Serial.println(measureInt);
#endif

    return measureInt; // *10 to keep one decimal
}