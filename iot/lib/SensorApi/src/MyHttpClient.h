#ifndef IOT_MYHTTPCLIENT_H
#define IOT_MYHTTPCLIENT_H

#include <HTTPClient.h>
#include "IClient.h"

class MyHttpClient: public IClient {
public:
    MyHttpClient();
    ~MyHttpClient();
    std::tuple<String, int> send(const char* type, const char *body, String url) override;
    void setURL(const char *serverEndpoint) override;
private:
    HTTPClient *_client;
};


#endif //IOT_MYHTTPCLIENT_H
