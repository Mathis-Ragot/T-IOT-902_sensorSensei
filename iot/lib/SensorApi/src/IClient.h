#ifndef IOT_ICLIENT_H
#define IOT_ICLIENT_H

class IClient {
public:
    virtual const char *send(const char *) = 0;
    virtual void setURL(const char *serverEndpoint) = 0;
};

#endif //IOT_ICLIENT_H
