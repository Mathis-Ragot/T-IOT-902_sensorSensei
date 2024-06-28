#include "test.h"

int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_optional_basic);

    RUN_TEST(test_printBits);
    RUN_TEST(test_countSignificantBits);
    RUN_TEST(test_printBytesAsCharacters);
    RUN_TEST(test_printBytesAsIntegers);
    RUN_TEST(test_printBytesAsHex);

    RUN_TEST(test_createMeasure);
    RUN_TEST(test_createMeasures);
    RUN_TEST(test_parseMeasureKind);
    RUN_TEST(test_getMeasureKindName);
    RUN_TEST(test_createMeasure_str_str);
    RUN_TEST(test_createMeasure_vec_kind);
    RUN_TEST(test_createMeasure_str_kind);
    RUN_TEST(test_createMeasures_vec);
    RUN_TEST(test_measure_toJson);
    RUN_TEST(test_measure_fromJson);
    RUN_TEST(test_create_measure_toJson);
    RUN_TEST(test_SensorApi_constructor);
    RUN_TEST(test_SensorApi_copy_constructor);
    RUN_TEST(test_SensorApi_setClient);
    RUN_TEST(test_SensorApi_getServerEndpoint);
    RUN_TEST(test_SensorApi_addMeasure);
    RUN_TEST(test_SensorApi_addMeasure_vec);
    RUN_TEST(test_SensorApi_addMeasure_optional);
    RUN_TEST(test_clearMeasures);
    RUN_TEST(test_send);
    RUN_TEST(test_getMeasures);
    RUN_TEST(test_send_vec);
    RUN_TEST(test_send_measure);

    RUN_TEST(test_createMeasure_vec_with_str);

    return UNITY_END();
}

int main(void) {
    return runUnityTests();
}