#include "Measure.h"

void test_createMeasure() {
    std::vector<String> value = {"value1", "value2"};
    MeasureKind kind = MeasureKind::Dust;
    Measure measure = createMeasure(value, kind);
    assert(measure.value == value);
    assert(measure.kind == kind);
}

void test_createMeasures() {
    CreateMeasures createMeasures;
    createMeasures.values.push_back(createMeasure({"value1", "value2"}, MeasureKind::Dust));
    createMeasures.values.push_back(createMeasure({"value1", "value2"}, MeasureKind::Dust));
    assert(createMeasures.values.size() == 2);
}