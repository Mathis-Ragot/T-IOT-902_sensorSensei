//
// Created by clement.mathe on 27/06/2024.
//

#include "SoundMeasure.h"
using namespace measure;

SoundMeasure::SoundMeasure() : AbstractMeasure(SOUND_SENSOR_DATA_BIT_LENGTH) {
}

//Retourne la valeur de la mesure de son en string
String SoundMeasure::getDeSerializedMeasure() {
    float value = static_cast<float>(measure::AbstractMeasure::rawMeasure) / 10.0f;

#ifdef RECEPTOR_DEBUG
    Serial.print("Sound : ");
    Serial.println(String(value, 1));
#endif
    return String(value, 1);
}