#include <unity.h>
#include "test.h"
#include "Measure.h"
#include <iostream>
#include "SensorApi.h"

class MockClient : public IClient {
    public:
    MockClient() {}
    std::tuple<string, int> send(const char* type, const char *body, string url) {
        return std::make_tuple("{}", 200);
    }

    void setURL(const char *serverEndpoint) {

    }
};

void test_createMeasure() {
    std::vector<string> value = {"value1", "value2"};
    MeasureKind kind = MeasureKind::Dust;
    Measure measure = createMeasure(value, kind);
    TEST_ASSERT_EQUAL(measure.value.size(), value.size());
    TEST_ASSERT_EQUAL(measure.kind, kind);
}

void test_createMeasures() {
    CreateMeasures createMeasures;
    createMeasures.values.push_back(createMeasure((std::vector<string>){"value1", "value2"}, MeasureKind::Dust));
    createMeasures.values.push_back(createMeasure((std::vector<string>){"value1", "value2"}, MeasureKind::Dust));
    TEST_ASSERT_EQUAL(createMeasures.values.size(), 2);
}


void test_createMeasure_vec_with_str() {
    auto a = createMeasure((const std::vector<string>){"1.2", "2.4"}, "dust");
    TEST_ASSERT_TRUE(a.has_value());
    TEST_ASSERT_EQUAL(a.value().value.size(), 2);
    TEST_ASSERT_EQUAL(a.value().kind, MeasureKind::Dust);

    auto b = createMeasure((const std::vector<string>){"1.2", "2.4"}, "abc");
    TEST_ASSERT_FALSE(b.has_value());
}

void test_parseMeasureKind() {
    auto a = parseMeasureKind("null");
    TEST_ASSERT_FALSE(a.has_value());
    auto b = parseMeasureKind("dust");
    TEST_ASSERT_TRUE(b.has_value());
}

void test_getMeasureKindName() {
    auto a = getMeasureKindName(MeasureKind::Dust);
    TEST_ASSERT_EQUAL_STRING(a.c_str(), "dust");
}

void test_createMeasure_str_str() {
    auto a = createMeasure("1.5", "dust");
    TEST_ASSERT_TRUE(a.has_value());
    auto b = createMeasure("a", "b");
    TEST_ASSERT_FALSE(b.has_value());
}

void test_createMeasure_vec_kind() {
    auto a = createMeasure((std::vector<string>){"1.2", "2.4"}, MeasureKind::Dust);
    TEST_ASSERT_TRUE(a.kind == MeasureKind::Dust);
}

void test_createMeasure_str_kind() {
    auto a = createMeasure("1.2", MeasureKind::Dust);
    TEST_ASSERT_TRUE(a.kind == MeasureKind::Dust);
}

void test_createMeasures_vec() {
    auto a = createMeasures((std::vector<Measure>){createMeasure((std::vector<string>){"1.2", "2.4"}, MeasureKind::Dust)});
    TEST_ASSERT_TRUE(a.values.size() == 1);
}

void test_measure_toJson() {
    auto a = createMeasure("1.2", MeasureKind::Dust);
    auto b = a.toJson();
    TEST_ASSERT_TRUE(b.size() > 0);
}

void test_measure_fromJson() {
    auto a = createMeasure("1.2", MeasureKind::Dust);
    auto b = a.toJson();
    auto c = Measure::fromJson(b);
    TEST_ASSERT_TRUE(c.kind == MeasureKind::Dust);
}

void test_create_measure_toJson() {
    auto a = createMeasures((std::vector<Measure>){createMeasure((std::vector<string>){"1.2", "2.4"}, MeasureKind::Dust)});
    auto b = a.toJson();
    TEST_ASSERT_TRUE(b.size() > 0);
}

void test_SensorApi_constructor() {
    auto client = std::make_shared<MockClient>();
    SensorApi sensorApi(client, "test");
    TEST_ASSERT_NOT_NULL(sensorApi.getClient());
}

void test_SensorApi_copy_constructor() {
    auto client = std::make_shared<MockClient>();
    SensorApi sensorApi(client, "test");
    SensorApi sensorApi2(sensorApi);
}

void test_SensorApi_setClient() {
    auto client = std::make_shared<MockClient>();
    SensorApi sensorApi(client, "test");
    auto client2 = std::make_shared<MockClient>();
    sensorApi.setClient(client2);
    TEST_ASSERT_NOT_NULL(sensorApi.getClient());
}

void test_SensorApi_getServerEndpoint() {
    auto client = std::make_shared<MockClient>();
    SensorApi sensorApi(client, "test");
    TEST_ASSERT_EQUAL_STRING(sensorApi.getServerEndpoint().c_str(), "test");
}

void test_SensorApi_addMeasure() {
    auto client = std::make_shared<MockClient>();
    SensorApi sensorApi(client, "test");
    Measure measure = createMeasure("1.2", MeasureKind::Dust);
    auto a = sensorApi.addMeasure(measure);
    TEST_ASSERT_EQUAL(std::get<0>(a), Success);
}

void test_SensorApi_addMeasure_vec() {
    auto client = std::make_shared<MockClient>();
    SensorApi sensorApi(client, "test");
    std::vector<Measure> measures = {createMeasure("1.2", MeasureKind::Dust)};
    auto a = sensorApi.addMeasure(measures);
    TEST_ASSERT_EQUAL(std::get<0>(a), Success);
}

void test_SensorApi_addMeasure_optional() {
    auto client = std::make_shared<MockClient>();
    SensorApi sensorApi(client, "test");
    tl::optional<Measure> measure = createMeasure("1.2", MeasureKind::Dust);
    auto a = sensorApi.addMeasure(measure);
    TEST_ASSERT_EQUAL(std::get<0>(a), Success);
    tl::optional<Measure> measureb = createMeasure("1.2", "null");
    auto b = sensorApi.addMeasure(measureb);
    TEST_ASSERT_EQUAL(std::get<0>(b), InvalidMeasure);
}

void test_clearMeasures() {
    auto client = std::make_shared<MockClient>();
    SensorApi sensorApi(client, "test");
    Measure measure = createMeasure("1.2", MeasureKind::Dust);
    sensorApi.addMeasure(measure);
    sensorApi.clearMeasures();
}

void test_send() {
    auto client = std::make_shared<MockClient>();
    SensorApi sensorApi(client, "test");
    Measure measure = createMeasure("1.2", MeasureKind::Dust);
    sensorApi.addMeasure(measure);
    auto a = sensorApi.send();
    TEST_ASSERT_EQUAL(std::get<0>(a), Success);
}

void test_getMeasures() {
    auto client = std::make_shared<MockClient>();
    SensorApi sensorApi(client, "test");
    Measure measure = createMeasure("1.2", MeasureKind::Dust);
    sensorApi.addMeasure(measure);
    auto a = sensorApi.getMeasures();
    TEST_ASSERT_EQUAL(std::get<0>(a), Success);
}

void test_send_vec() {
    auto client = std::make_shared<MockClient>();
    SensorApi sensorApi(client, "test");
    std::vector<Measure> measures = {createMeasure("1.2", MeasureKind::Dust)};
    auto a = sensorApi.send(measures);
    TEST_ASSERT_EQUAL(std::get<0>(a), Success);
}

void test_send_measure() {
    auto client = std::make_shared<MockClient>();
    SensorApi sensorApi(client, "test");
    auto measure = createMeasure("1.2", MeasureKind::Dust);
    auto a = sensorApi.send(measure);
    TEST_ASSERT_EQUAL(std::get<0>(a), Success);
}