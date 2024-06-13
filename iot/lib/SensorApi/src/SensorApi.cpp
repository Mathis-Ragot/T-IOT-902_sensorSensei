#include "SensorApi.h"

SensorApi::SensorApi(std::shared_ptr<IClient> client, string serverEndpoint) : _serverEndpoint(std::move(serverEndpoint)) {
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

string SensorApi::getServerEndpoint() const noexcept{
    return this->_serverEndpoint;
}

std::tuple<SensorResponseKind, string> SensorApi::addMeasure(Measure &measure) noexcept {
    this->_queues.push_back(measure);
    return std::make_tuple(Success, "Measure added");
}

std::tuple<SensorResponseKind, string> SensorApi::addMeasure(std::vector<Measure> &measures) noexcept {
    for (auto &measure: measures) {
        this->_queues.push_back(measure);
    }
    return std::make_tuple(Success, "Measure added");
}

std::tuple<SensorResponseKind, string> SensorApi::addMeasure(tl::optional<Measure> &measure) noexcept {
    if (measure.has_value()) {
        this->_queues.push_back(measure.value());
        return std::make_tuple(Success, "Measure added");
    } else {
        return std::make_tuple(InvalidMeasure, "No measure to add !");
    }
}


void SensorApi::clearMeasures() noexcept {
    this->_queues.clear();
}

std::tuple<SensorResponseKind, SensorApiError> SensorApi::send() noexcept {
    auto measuresToSend = createMeasures(this->_queues);

    string url = (string(this->_serverEndpoint) + MEASURE_ENDPOINT);
    const auto [body, code] = this->_client->send(CREATE_MEASURE_METHOD_TYPE, measuresToSend.toJson().c_str(), url);
#ifdef SENSOR_API_DEBUG
    printf("Code: %i\n", code);
    printf("Body: %s\n", body.c_str());
#endif
    return std::make_tuple(code == 200 ? Success : Failed, std::make_tuple(body, code));
}

std::tuple<SensorResponseKind, SensorApiError, std::vector<Measure>> SensorApi::getMeasures() const noexcept {
    string url = (string(this->_serverEndpoint) + MEASURE_ENDPOINT);
    const auto [body, code] = this->_client->send(LIST_MEASURE_METHOD_TYPE, "", url);
#ifdef SENSOR_API_DEBUG
    printf("Code: %i\n", code);
    printf("Body: %s\n", body.c_str());
#endif
    return std::make_tuple(code == 200 ? Success : Failed, std::make_tuple(body, code), std::vector<Measure>());
}

std::tuple<SensorResponseKind, SensorApiError> SensorApi::send(std::vector<Measure> &measures) const noexcept {
    auto measuresToSend = createMeasures(measures);
    string url = (string(this->_serverEndpoint) + MEASURE_ENDPOINT);
    const auto [body, code] = this->_client->send(CREATE_MEASURE_METHOD_TYPE, R"({"values": [{"value": ["13.2", "15.20"], "kind": "Dust"}]})", url);
#ifdef SENSOR_API_DEBUG
    printf("Code: %i\n", code);
    printf("Body: %s\n", body.c_str());
#endif
    return std::make_tuple(Success, std::make_tuple(body, code));
}

std::tuple<SensorResponseKind, SensorApiError> SensorApi::send(Measure &measure) const noexcept {
    auto measuresToSend = createMeasures(std::vector<Measure>{measure});
    string url = (string(this->_serverEndpoint) + MEASURE_ENDPOINT);
    const auto [body, code] = this->_client->send(CREATE_MEASURE_METHOD_TYPE, R"({"values": [{"value": ["13.2", "15.20"], "kind": "Dust"}]})", url);
#ifdef SENSOR_API_DEBUG
    printf("Code: %i\n", code);
    printf("Body: %s\n", body.c_str());
#endif
    return std::make_tuple(code == 200 ? Success : Failed, std::make_tuple(body, code));
}

SensorApi::~SensorApi() = default;