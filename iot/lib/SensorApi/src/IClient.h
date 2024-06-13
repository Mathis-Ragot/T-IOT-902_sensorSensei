#ifndef IOT_ICLIENT_H
#define IOT_ICLIENT_H

using namespace std;

class IClient {
public:
    virtual std::tuple<string, int> send(const char* type, const char *body, string url) = 0;
    virtual void setURL(const char *serverEndpoint) = 0;
};

#endif //IOT_ICLIENT_H
