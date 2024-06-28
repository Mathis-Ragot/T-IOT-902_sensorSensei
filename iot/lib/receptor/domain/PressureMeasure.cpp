//
// Created by clement.mathe on 27/06/2024.
//

#include "PressureMeasure.h"

using namespace measure;

PressureMeasure::PressureMeasure() : AbstractMeasure(PRESSURE_SENSOR_DATA_BIT_LENGTH,
                                                     SensorInfos(
                                                             PRESSURE_SENSOR_ID,
                                                             PRESSURE_SENSOR_REF,
                                                             std::vector<SensorType>{SensorInfos::stringToSensorType(PRESSURE_SENSOR_TYPE)})) {
}

//Retourne la valeur de la mesure de pression en string
String PressureMeasure::getDeSerializedMeasure() {
#ifdef RECEPTOR_DEBUG
    Serial.print("Pressure : ");
    auto hpa = static_cast<float>(measure::AbstractMeasure::rawMeasure) / 100.0f;
    Serial.println(String(hpa, 1));
#endif
    return String(measure::AbstractMeasure::rawMeasure);
}