#include "HumiditySensor.h"
#include "domain/Sensor/Sensors.h"

void sensor::HumiditySensor::begin()
{
    this->dht->begin();
}

float sensor::HumiditySensor::getMeasure()
{
    float humidity = this->dht->readHumidity();

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %");
    Serial.println();

    return humidity;
}

sensor::HumiditySensor::HumiditySensor() : AbstractSensor()
{
    this->dht = new DHT(dhtPin, dht11);

    this->dataBitLength = HUMIDITY_SENSOR_DATA_BIT_LENGTH;
    this->infos = SensorInfos(
        HUMIDITY_SENSOR_ID,
        HUMIDITY_SENSOR_REF,
        std::vector<SensorType>{SensorInfos::stringToSensorType(HUMIDITY_SENSOR_TYPE)});
}

sensor::HumiditySensor::~HumiditySensor()
{
    delete this->dht;
}

uint16_t sensor::HumiditySensor::getSerializedMeasure()
{
    float measure = getMeasure();
    int measureInt = static_cast<int>(std::round(measure));
    if (measureInt > MaxMeasureSize)
    {
        measureInt = MaxMeasureSize; // Cap the value to fit within 12 bits
    }

    Serial.print("Humidity serialized: ");
    Serial.println(measureInt);


    return static_cast<uint16_t>(measureInt);
}
