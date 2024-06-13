//
// Created by clement.mathe on 18/04/2024.
//

#include "DustSensor.h"
#include "domain/Sensor/Sensors.h"

void sensor::DustSensor::begin()
{
    analogReadResolution(12);       // Configure la résolution ADC à 12 bits
    analogSetAttenuation(ADC_11db); // Configure l'atténuation pour lire jusqu'à environ 3.3V
}

float sensor::DustSensor::getMeasure()
{
    digitalWrite(ledPower, LOW);         // power on the LED
    delayMicroseconds(samplingTime);     //
    voMeasured = analogRead(measurePin); // read the dust value//
    delayMicroseconds(deltaTime);
    digitalWrite(ledPower, HIGH); // turn the LED off
    delayMicroseconds(sleepTime); //
    calcVoltage = voMeasured * (3.2 / 4096.0);

    Serial.print("Voltage: ");
    Serial.print(voMeasured);
    Serial.print(" ");
    // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
    dustDensity = 170 * calcVoltage - 0.1;

    Serial.print("PM2.5= ");
    Serial.print(dustDensity);
    Serial.print(" ug/m3");
    Serial.println();

    return this->dustDensity;
}

sensor::DustSensor::DustSensor() : AbstractSensor()
{

    this->dataBitLength = DUST_SENSOR_DATA_BIT_LENGTH;
    this->infos = SensorInfos(
        DUST_SENSOR_ID,
        DUST_SENSOR_REF,
        std::vector<SensorType>{SensorInfos::stringToSensorType(DUST_SENSOR_TYPE)});

    pinMode(ledPower, OUTPUT);
    pinMode(measurePin, INPUT);
}

uint16_t sensor::DustSensor::getSerializedMeasure()
{
    float measure = getMeasure();
    int measureInt = static_cast<int>(std::round(measure));
    if (measureInt > MaxMeasureSize) {
        measureInt = MaxMeasureSize;  // Cap the value to fit within 12 bits
    }

    return static_cast<uint16_t>(measureInt);
}
