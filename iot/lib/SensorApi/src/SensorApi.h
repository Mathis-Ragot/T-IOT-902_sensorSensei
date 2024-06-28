#ifndef IOT_SENSORAPI_H
#define IOT_SENSORAPI_H

#include <memory>

#include "Measure.h"
#include "IClient.h"

#define MEASURE_ENDPOINT "/measure/"
#define CREATE_MEASURE_METHOD_TYPE "POST"
#define LIST_MEASURE_METHOD_TYPE "GET"

/**
 * Enum for the response of the sensor api
 */
enum SensorResponseKind {
    Success,
    Failed,
    InvalidMeasure
};

typedef std::tuple<string, int> SensorApiError;
typedef std::tuple<SensorResponseKind, SensorApiError> SensorApiResponse;
typedef std::tuple<SensorResponseKind, SensorApiError, std::vector<Measure>> SensorApiMeasureResponse;
typedef std::tuple<SensorResponseKind, string> SensorResponse;
typedef std::shared_ptr<IClient> SensorClient;

class SensorApi {
public:
    /**
     * Constructor
     * @param serverEndpoint
     */
    SensorApi(SensorClient client, string serverEndpoint);
    /**
     * Copy constructor
     * @param sensorApi
     */
    SensorApi(SensorApi &sensorApi);
    /**
     * Get the client
     * @return
     */
    [[nodiscard]] IClient* getClient() const;
    /**
     * Set the client
     * @param client
     */
    void setClient(std::shared_ptr<IClient> client);
    /**
     * Send all measures in queues to the api
     * @return SensorResponseKind
     */
    SensorApiResponse send() noexcept;

    /**
     * Get all measures from the api
     * @return tuple of SensorResponseKind and vector of Measure
     */
    [[nodiscard]] SensorApiMeasureResponse getMeasures() const noexcept;
    /**
     * Send a list of measures to the api (without queues)
     * @param measures
     * @return SensorResponseKind
     */
    [[nodiscard]] SensorApiResponse send(std::vector<Measure> &measures) const noexcept;
    /**
     * Send a single measure to the api (without queues)
     * @param measure
     * @return SensorResponseKind
     */
    [[nodiscard]] SensorApiResponse send(Measure &measure) const noexcept;
    /**
     * Add a measure to the queues
     * @param measure
     * @return SensorResponseKind
     */
    SensorResponse addMeasure(Measure &measure) noexcept;
    /**
     * Add a list of measures to the queues
     * @param measures
     * @return SensorResponseKind
     */
    SensorResponse addMeasure(std::vector<Measure> &measures) noexcept;
    /**
     * Add a measure to the queues
     * @param measure
     * @return
     */
    SensorResponse addMeasure(tl::optional<Measure> &measure) noexcept;
    /**
     * Clear all measures in the queues
     */
    void clearMeasures() noexcept;
    /**
     * Get the server endpoint
     * @return
     */
    [[nodiscard]] string getServerEndpoint() const noexcept;
    /**
     * Destructor
     */
    ~SensorApi();
private:
    /**
     * The http client
     */
    SensorClient _client;
    /**
     * The server endpoint
     */
    string _serverEndpoint;
    /**
     * The queues of measures
     */
    std::vector<Measure> _queues;
};

#endif