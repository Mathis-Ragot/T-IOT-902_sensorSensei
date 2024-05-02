#include "SensorApi.h"

#include <utility>

SensorApi::SensorApi(std::shared_ptr<IClient> client, String serverEndpoint) : _serverEndpoint(std::move(serverEndpoint)) {
    this->_client = std::move(client);
    this->_client->setURL(this->_serverEndpoint.c_str());
}

SensorApi::SensorApi(SensorApi &sensorApi) {
    this->_client = sensorApi._client;
    this->_serverEndpoint = sensorApi._serverEndpoint;
}

IClient *SensorApi::getClient() const {
    return this->_client.get();
}

void SensorApi::setClient(std::shared_ptr<IClient> client) {
    this->_client = std::move(client);
}

String SensorApi::getServerEndpoint() const {
    return this->_serverEndpoint;
}

SensorResponse SensorApi::addMeasure(Measure measure) {
    this->_queues.push_back(std::move(measure));
    return Success;
}

SensorResponse SensorApi::addMeasure(std::vector<Measure> measures) {
    for (auto &measure: measures) {
        this->_queues.push_back(std::move(measure));
    }
    return Success;
}

SensorResponse SensorApi::addMeasure(std::optional<Measure> measure) {
    if (measure.has_value()) {
        this->_queues.push_back(measure.value());
        return Success;
    } else {
        return InvalidMeasure;
    }
}


void SensorApi::clearMeasures() {
    this->_queues.clear();
}

SensorResponse SensorApi::send() {
    createMeasures(this->_queues);
    this->_client->send((String(this->_serverEndpoint) + "/measure/").c_str());
    return Success;
}

SensorResponse SensorApi::send(std::vector<Measure> measures) const {
    return Success;
}

SensorResponse SensorApi::send(Measure measure) const {
    return Success;
}

SensorApi::~SensorApi() = default;