#ifndef IOT_MEASURE_H
#define IOT_MEASURE_H

#include <vector>
#include <ArduinoJson.h>
#include "optional.hpp"

enum MeasureKind {
    Dust,
    Temperature,
    Humidity,
    Pressure,
    SoundLevel,
};

struct Measure {
    std::vector<String> value;
    MeasureKind kind;
    String toJson();
    static Measure fromJson(String);
};

struct CreateMeasures {
    std::vector<Measure> values;
    String toJson();
};

struct MeasureKindMap {
    MeasureKindMap(String, MeasureKind);
    String name;
    MeasureKind kind;
};

const MeasureKindMap measureKindMaps[] = {{"dust", Dust}, {"temperature", Temperature}, {"humidity", Humidity}, {"pressure", Pressure}, {"sound_level", SoundLevel}};

tl::optional<Measure> createMeasure(const std::vector<String>& value, const String& kind);
tl::optional<Measure> createMeasure(String value, const String& kind);
tl::optional<MeasureKind> parseMeasureKind();
Measure createMeasure(std::vector<String> value, MeasureKind kind);
Measure createMeasure(String value, MeasureKind kind);
CreateMeasures createMeasures(std::vector<Measure> measures);

#endif
