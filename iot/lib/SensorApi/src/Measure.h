#ifndef IOT_MEASURE_H
#define IOT_MEASURE_H

#include <optional>
#include <vector>
#include <ArduinoJson.h>

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

const MeasureKindMap measureKindMaps[] = {{"Dust", Dust}, {"Temperature", Temperature}, {"Humidity", Humidity}, {"Pressure", Pressure}, {"Soundlevel", SoundLevel}};

std::optional<Measure> createMeasure(const std::vector<String>& value, const String& kind);
std::optional<Measure> createMeasure(String value, const String& kind);
std::optional<MeasureKind> parseMeasureKind();
Measure createMeasure(std::vector<String> value, MeasureKind kind);
Measure createMeasure(String value, MeasureKind kind);
CreateMeasures createMeasures(std::vector<Measure> measures);

#endif
