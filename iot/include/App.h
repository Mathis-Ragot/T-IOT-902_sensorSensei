#ifndef ARGAMES_IOT_APP
#define ARGAMES_IOT_APP


#include <iostream>
#include "manager/DeviceManager/EmitterDeviceManager.h"
#include "Arduino.h"


class App {
public:
    App();
    ~App();
    void loop();
};

#endif //ARGAMES_IOT_APP