#ifndef IOT_SENSORAPI_H
#define IOT_SENSORAPI_H

#include <vector>
#include <memory>

#include "Measure.h"
#include "IClient.h"

/**
 * Enum for the response of the sensor api
 */
enum SensorResponse {
    Success,
    Failed,
    InvalidMeasure
};

class SensorApi {
public:
    /**
     * Constructor
     * @param serverEndpoint
     */
    SensorApi(std::shared_ptr<IClient> client, String serverEndpoint);
    /**
     * Copy constructor
     * @param sensorApi
     */
    SensorApi(SensorApi &sensorApi);
    /**
     * Get the client
     * @return
     */
    IClient* getClient() const;
    /**
     * Set the client
     * @param client
     */
    void setClient(std::shared_ptr<IClient> client);
    /**
     * Send all measures in queues to the api
     * @return SensorResponse
     */
    SensorResponse send();

    /**
     * Send a list of measures to the api (without queues)
     * @param measures
     * @return SensorResponse
     */
    SensorResponse send(std::vector<Measure> measures) const;
    /**
     * Send a single measure to the api (without queues)
     * @param measure
     * @return SensorResponse
     */
    SensorResponse send(Measure measure) const;
    /**
     * Add a measure to the queues
     * @param measure
     * @return SensorResponse
     */
    SensorResponse addMeasure(Measure measure);
    /**
     * Add a list of measures to the queues
     * @param measures
     * @return SensorResponse
     */
    SensorResponse addMeasure(std::vector<Measure> measures);
    /**
     * Add a measure to the queues
     * @param measure
     * @return
     */
    SensorResponse addMeasure(std::optional<Measure> measure);
    /**
     * Clear all measures in the queues
     */
    void clearMeasures();
    /**
     * Get the server endpoint
     * @return
     */
    String getServerEndpoint() const;
    /**
     * Destructor
     */
    ~SensorApi();
private:
    /**
     * The http client
     */
    std::shared_ptr<IClient> _client;
    /**
     * The server endpoint
     */
    String _serverEndpoint;
    /**
     * The queues of measures
     */
    std::vector<Measure> _queues;
};

#endif