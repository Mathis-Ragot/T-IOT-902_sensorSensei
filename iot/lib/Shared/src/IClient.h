#ifndef IOT_ICLIENT_H
#define IOT_ICLIENT_H

class IClient {
public:
    virtual std::tuple<String, int> send(const char* type, const char *body, String url) = 0;
    virtual void setURL(const char *serverEndpoint) = 0;
};

#endif //IOT_ICLIENT_H
