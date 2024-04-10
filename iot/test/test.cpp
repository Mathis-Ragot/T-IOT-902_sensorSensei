#include <unity.h>

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

int runUnityTests(void) {
    UNITY_BEGIN();
    return UNITY_END();
}

int main(void) {
    return runUnityTests();
}

// For Arduino framework
void setup() {
    runUnityTests();
}

// For Arduino framework
void loop() {}

// For ESP-IDF framework
void app_main() {
    runUnityTests();
}
