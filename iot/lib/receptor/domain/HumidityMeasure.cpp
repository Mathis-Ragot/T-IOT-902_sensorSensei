//
// Created by clement.mathe on 27/06/2024.
//

#include "HumidityMeasure.h"
using namespace measure;


    measure::HumidityMeasure::HumidityMeasure() : AbstractMeasure(HUMIDITY_SENSOR_DATA_BIT_LENGTH,
                                                                  SensorInfos(
                                                                          HUMIDITY_SENSOR_ID,
                                                                          HUMIDITY_SENSOR_REF,
                                                                          std::vector<SensorType>{SensorInfos::stringToSensorType(HUMIDITY_SENSOR_TYPE)})) {

}

//Retourne la valeur de la mesure d'humidité en string
String HumidityMeasure::getDeSerializedMeasure() {
#ifdef RECEPTOR_DEBUG
    Serial.print("Humidity : ");
    Serial.println(String(measure::AbstractMeasure::rawMeasure));
#endif
    return String(measure::AbstractMeasure::rawMeasure);
}
