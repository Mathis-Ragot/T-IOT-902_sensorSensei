#ifndef ARGAMES_IOT_APP
#define ARGAMES_IOT_APP


#include <iostream>
#include "EmitterDeviceManager.h"
#include "Arduino.h"


class EmitterApp {
public:
    EmitterApp();
    ~EmitterApp();
    void loop();
};

#endif //ARGAMES_IOT_APP