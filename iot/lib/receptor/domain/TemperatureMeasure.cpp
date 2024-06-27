//
// Created by clement.mathe on 27/06/2024.
//

#include "TemperatureMeasure.h"
using namespace measure;

TemperatureMeasure::TemperatureMeasure() : AbstractMeasure(TEMP_SENSOR_DATA_BIT_LENGTH) {
}

//Retourne la valeur de la mesure de température en string
String TemperatureMeasure::getDeSerializedMeasure() {
    float fahrenheit = static_cast<float>(measure::AbstractMeasure::rawMeasure) / 10.0f;
    float celsius = (fahrenheit - 32) * 5.0 / 9.0;
#ifdef RECEPTOR_DEBUG
    Serial.print("Temperature : ");
    Serial.println(String(celsius, 1));
#endif
    return String(celsius, 1);
}