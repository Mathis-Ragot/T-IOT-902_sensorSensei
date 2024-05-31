#include <unity.h>

int runUnityTests(void) {
    UNITY_BEGIN();
    return UNITY_END();
}

int main(void) {
    return runUnityTests();
}