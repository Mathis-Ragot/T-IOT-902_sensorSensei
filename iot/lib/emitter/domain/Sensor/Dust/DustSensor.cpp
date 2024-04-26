//
// Created by clement.mathe on 18/04/2024.
//

#include <iostream>
#include "DustSensor.h"

void sensor::DustSensor::begin() {
    analogReadResolution(12);  // Configure la résolution ADC à 12 bits
    analogSetAttenuation(ADC_11db);  // Configure l'atténuation pour lire jusqu'à environ 3.3V
}

float sensor::DustSensor::getMeasure() {
    digitalWrite(ledPower, LOW); // power on the LED
    delayMicroseconds(samplingTime);//
    voMeasured = analogRead(measurePin); // read the dust value//
    delayMicroseconds(deltaTime);
    digitalWrite(ledPower, HIGH); // turn the LED off
    delayMicroseconds(sleepTime);//
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

sensor::DustSensor::DustSensor() : AbstractSensor() {

    this->infos = SensorInfos(
            DUST_SENSOR_ID,
            DUST_SENSOR_REF,
            std::vector<SensorType>{SensorInfos::stringToSensorType(DUST_SENSOR_TYPE)}
    );

    pinMode(ledPower, OUTPUT);
    pinMode(measurePin, INPUT);

}

// Fonction pour imprimer les bits d'un nombre
void static printBits(int value, int numBits) {
    Serial.print("Bits: ");
    for (int i = numBits - 1; i >= 0; --i) {
        Serial.print((value >> i) & 1);
    }
    Serial.println();
}

// Fonction pour compter le nombre de bits significatifs
int countSignificantBits(int value) {
    int bits = 0;
    while (value > 0) {
        bits++;
        value >>= 1;
    }
    Serial.print("Bits: ");
    Serial.print(bits);
    return bits;
}

std::vector<bool> sensor::DustSensor::getSerializedMeasure() {
    float measure = 4095;
    int measureInt = static_cast<int>(std::round(measure));
    if (measureInt > 4095) {
        measureInt = 4095;  // Cap the value to fit within 12 bits
    }

//    printBits(static_cast<uint8_t>(measureInt & 0xFFF), 12);
//    countSignificantBits(static_cast<uint8_t>(measureInt & 0xFFF));

    std::vector<bool> result(12);

    for (int i = 0; i < 12; ++i) {
        result[i] = (measureInt >> i) & 1;
    }

    Serial.print("Serialized: ");
    for (bool bit : result) {
        Serial.print(bit);
    }

    Serial.println();
    Serial.println(result.size());

    return result;
}


