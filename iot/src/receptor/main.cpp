#include "ReceptorApp.h"

ReceptorApp* app;

void setup() {
    app = new ReceptorApp();
}

void loop() {
    app->loop();
}