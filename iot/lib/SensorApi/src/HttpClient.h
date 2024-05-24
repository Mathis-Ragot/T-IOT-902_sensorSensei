#ifndef IOT_HTTPCLIENT_H
#define IOT_HTTPCLIENT_H

#include <HTTPClient.h>
#include "IClient.h"

class HttpClient: public IClient {
public:
    HttpClient();
    ~HttpClient();
    std::tuple<String, int> send(const char* type, const char *body, String url) override;
    void setURL(const char *serverEndpoint) override;
private:
    HTTPClient *_client;
};


#endif //IOT_HTTPCLIENT_H
