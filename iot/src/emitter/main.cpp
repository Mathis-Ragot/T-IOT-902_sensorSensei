#include <vector>
#include "EmitterApp.h"

EmitterApp *app;

void setup() {
    app = new EmitterApp();
}

void loop() {
    app->loop();
}







