#ifdef ENABLE_IOT_HTTP_CLIENT

#ifndef IOT_HTTPCLIENT_H
#define IOT_HTTPCLIENT_H

#include <HTTPClient.h>
#include "IClient.h"

using namespace std;

class HttpClient: public IClient {
public:
    HttpClient();
    ~HttpClient();
    std::tuple<string, int> send(const char* type, const char *body, string url) override;
    void setURL(const char *serverEndpoint) override;
private:
    HTTPClient *_client;
};


#endif //IOT_HTTPCLIENT_H

#endif