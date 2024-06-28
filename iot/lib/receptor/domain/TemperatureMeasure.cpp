//
// Created by clement.mathe on 27/06/2024.
//

#include "TemperatureMeasure.h"
using namespace measure;

TemperatureMeasure::TemperatureMeasure() : AbstractMeasure(TEMP_SENSOR_DATA_BIT_LENGTH,
                                                           SensorInfos(
                                                                   TEMP_SENSOR_ID,
                                                                   TEMP_SENSOR_REF,
                                                                   std::vector<SensorType>{SensorInfos::stringToSensorType(TEMP_SENSOR_TYPE)})) {
}

//Retourne la valeur de la mesure de température en string
String TemperatureMeasure::getDeSerializedMeasure() {
    float fahrenheit = static_cast<float>(measure::AbstractMeasure::rawMeasure) / 10.0f;
    float celsius = (fahrenheit - 32) * 5.0f / 9.0f;
#ifdef RECEPTOR_DEBUG
    Serial.print("Temperature : ");
    Serial.println(String(celsius, 1));
#endif
    return String(celsius, 1);
}