//
// Created by clavi on 10/05/2024.
//

#include "Arduino.h"
#include "domain/Sensor/AbstractSensor.h"
#include "soc/i2s_reg.h"
#include <driver/i2s.h>
#include <iomanip>

#ifndef IOT_SOUNDSENSOR_H
#define IOT_SOUNDSENSOR_H

constexpr u_int16_t BufferSize = 256;

namespace sensor {

    class SoundSensor : public AbstractSensor {

    public:
        explicit SoundSensor();

        void begin() override;

        float getMeasure() override;

        uint16_t getSerializedMeasure() override;

    private:
        int blckPin = SOUND_SENSOR_PIN_BCLK;
        int doutPin = SOUND_SENSOR_PIN_DOUT;
        int lrclPin = SOUND_SENSOR_PIN_LRCL;

        i2s_port_t i2sPort = I2S_NUM_0;
        int32_t buffer[BufferSize] {};
        u_int32_t sampleRate = 22050;
        i2s_bits_per_sample_t bitsPerSample = I2S_BITS_PER_SAMPLE_32BIT;
        i2s_channel_fmt_t channelFormat = I2S_CHANNEL_FMT_RIGHT_LEFT;

        const i2s_config_t i2sConfig = {
            .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
            .sample_rate = sampleRate,
            .bits_per_sample = bitsPerSample,
            .channel_format = channelFormat,
            .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_STAND_I2S),
            .intr_alloc_flags = 0,
            .dma_buf_count = 8,
            .dma_buf_len = 64,
            .use_apll = false
        };

        const i2s_pin_config_t pinConfig = {
            .bck_io_num = blckPin,
            .ws_io_num = lrclPin,
            .data_out_num = I2S_PIN_NO_CHANGE,
            .data_in_num = doutPin
        };

        void installDriver() const;
        void setPinConfig() const;
        static float convertToDecibels(float value);

    };

}

#endif //IOT_SOUNDSENSOR_H
