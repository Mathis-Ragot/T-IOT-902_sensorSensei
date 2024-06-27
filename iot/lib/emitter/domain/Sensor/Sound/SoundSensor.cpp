//
// Created by clavi on 10/05/2024.
//

#include "SoundSensor.h"
#include "domain/Sensor/Sensors.h"

sensor::SoundSensor::SoundSensor() : AbstractSensor() {
    this->dataBitLength = SOUND_SENSOR_DATA_BIT_LENGTH;
    this->infos = SensorInfos(
            SOUND_SENSOR_ID,
            SOUND_SENSOR_REF,
            std::vector<SensorType>{SensorInfos::stringToSensorType(SOUND_SENSOR_TYPE)}
    );
}

void sensor::SoundSensor::installDriver() const {
    i2s_driver_install(this->i2sPort, &this->i2sConfig, I2SQueueSize, nullptr);
    REG_SET_BIT(I2S_TIMING_REG(this->i2sPort), MicTimingShiftBit);
    REG_SET_BIT(I2S_CONF_REG(this->i2sPort), I2S_RX_MSB_SHIFT);
}

void sensor::SoundSensor::setPinConfig() const {
    i2s_set_pin(this->i2sPort, &this->pinConfig);
}

void sensor::SoundSensor::begin() {
    this->installDriver();
    this->setPinConfig();
}

float sensor::SoundSensor::convertToDecibels(float value) {
    return DecibelFactor * log10(value);
}

float sensor::SoundSensor::getMeasure() {
    size_t a;
    i2s_read(this->i2sPort, buffer, sizeof(buffer), &a, portMAX_DELAY);

    auto cleanBuffer = std::vector<int32_t>(BufferSize / 2, 0);

    int cleanBufIdx = 0;
    for (int i: buffer) {
        // Exclude values from other channel
        if (i != 0) {
            cleanBuffer[cleanBufIdx] = i >> ChannelBufferExclude;
            cleanBufIdx++;
        }
    }

    float meanValue = 0;
    int volumeCount = 0;
    for (int i: cleanBuffer) {
        if (i != 0) {
            meanValue += i;
            volumeCount++;
        }
    }
    meanValue /= static_cast<float>(volumeCount);

    // Subtract it from all sapmles to get a 'normalized' output
    for (int i = 0; i < volumeCount; i++) {
        cleanBuffer[i] -= static_cast<int32_t>(meanValue);
    }

    // Find the 'peak to peak' max
    float maxSample = MaxSamplePeak;
    float minSample = MinSamplePeak;
    for (int i = 0; i < volumeCount; i++) {
        minSample = _min(minSample, static_cast<float>(cleanBuffer[i]));
        maxSample = _max(maxSample, static_cast<float>(cleanBuffer[i]));
    }

    float measure = sensor::SoundSensor::convertToDecibels(maxSample - minSample);

    #ifdef SOUND_SENSOR_DEBUG
        Serial.print("Volume: ");
        Serial.print(measure);
        Serial.println(" dB");
    #endif

    return measure;
}

uint16_t sensor::SoundSensor::getSerializedMeasure() {
    float measure = getMeasure();

    // Cap the value to fit within 12 bits
    if (measure > MaxMeasureSize) {
        measure = MaxMeasureSize;
    }

#ifdef SOUND_SENSOR_DEBUG
    Serial.print("Volume Serialized: ");
    Serial.print(static_cast<uint16_t>(measure*10));
    Serial.println();
#endif
    return static_cast<uint16_t>(measure * 10); // *10 to keep one decimal
}
