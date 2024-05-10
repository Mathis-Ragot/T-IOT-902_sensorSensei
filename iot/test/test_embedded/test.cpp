#include <HTTPClient.h>

#include <unity.h>
#include "test.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_createMeasure);
    RUN_TEST(test_createMeasures);
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