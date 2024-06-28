#ifndef IOT_TEST_H
#define IOT_TEST_H

#include <unity.h>

void test_createMeasure();
void test_createMeasures();
void test_createMeasure_vec_with_str();
void test_parseMeasureKind();
void test_getMeasureKindName();
void test_createMeasure_str_str();
void test_createMeasure_vec_kind();
void test_createMeasure_str_kind();
void test_createMeasures_vec();
void test_measure_toJson();
void test_measure_fromJson();
void test_create_measure_toJson();
void test_SensorApi_constructor();
void test_SensorApi_copy_constructor();
void test_SensorApi_setClient();
void test_SensorApi_getServerEndpoint();
void test_SensorApi_addMeasure();
void test_SensorApi_addMeasure_vec();
void test_SensorApi_addMeasure_optional();
void test_clearMeasures();
void test_send();
void test_getMeasures();
void test_send_vec();
void test_send_measure();

void test_optional_basic();

void test_printBits();
void test_countSignificantBits();
void test_printBytesAsCharacters();
void test_printBytesAsIntegers();
void test_printBytesAsHex();

#endif