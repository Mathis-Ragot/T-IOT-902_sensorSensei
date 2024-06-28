//
// Created by clement.mathe on 18/04/2024.
//

#include "DustSensor.h"
#include "domain/Sensor/Sensors.h"

void sensor::DustSensor::begin()
{
    pinMode(measurePin, OUTPUT);
    digitalWrite(measurePin, LOW);
}


void sensor::DustSensor::readMeasure(int sample = 0) {
    // We read 10 samples + 1 to compute the mean, since we will ignore the first one
    if (sample == NUM_SAMPLES + 1) {
        return;
    }

    digitalWrite(measurePin, HIGH);
    delayMicroseconds(samplingTime);
    adcValues[adcIndex] = analogRead(ledPower);

    // We ignore the first value read since it is always 0
    if (adcIndex != 0) {
        sumAdcValues += adcValues[adcIndex];
    }

    adcIndex++;
    numReadings++;

    delayMicroseconds(deltaTime);
    digitalWrite(measurePin, LOW);
    delay(sleepTime);

    readMeasure(sample + 1);
}


float sensor::DustSensor::getMeasure()
{
    readMeasure();

    adcIndex = 0;

    // Compute average ADC value
    adcValue = sumAdcValues / NUM_SAMPLES;

    sumAdcValues = 0;
    numReadings = 0;

    // Calculate voltage
    voltage = (sysVoltage / (pow(2, adcResolution))) * adcValue * 11;

    // Calculate density
    if (voltage >= noDustVoltage) {
        voltage -= noDustVoltage;
        density = voltage * covRatio;
    } else {
        density = 0;
    }

    Serial.print("Dust : ");
    Serial.print(density);
    Serial.print(" ug/m3\n");

    return density;
}

sensor::DustSensor::DustSensor() : AbstractSensor()
{
    this->dataBitLength = DUST_SENSOR_DATA_BIT_LENGTH;
    this->infos = SensorInfos(
        DUST_SENSOR_ID,
        DUST_SENSOR_REF,
        std::vector<SensorType>{SensorInfos::stringToSensorType(DUST_SENSOR_TYPE)});
}

uint16_t sensor::DustSensor::getSerializedMeasure()
{
    float measure = getMeasure();
    int measureInt = static_cast<int>(std::round(measure));
    if (measureInt > MaxMeasureSize) {
        measureInt = MaxMeasureSize;  // Cap the value to fit within 12 bits
    }

    Serial.print("Dust serialized: ");
    Serial.println(measureInt);

    return static_cast<uint16_t>(measureInt);
}
