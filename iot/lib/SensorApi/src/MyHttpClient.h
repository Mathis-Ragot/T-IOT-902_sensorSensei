#ifdef ENABLE_IOT_HTTP_CLIENT

#ifndef IOT_MYHTTPCLIENT_H
#define IOT_MYHTTPCLIENT_H

#include <HTTPClient.h>
#include "IClient.h"

using namespace std;

class MyHttpClient: public IClient {
public:
    MyHttpClient();
    ~MyHttpClient();
    std::tuple<string, int> send(const char* type, const char *body, string url) override;
    void setURL(const char *serverEndpoint) override;
private:
    HTTPClient *_client;
};


#endif //IOT_MYHTTPCLIENT_H

#endif