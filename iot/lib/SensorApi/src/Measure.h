#ifndef IOT_MEASURE_H
#define IOT_MEASURE_H

#include <vector>
#include <ArduinoJson.h>
#include "optional.hpp"
#include <string>

using namespace std;

enum MeasureKind {
    Dust,
    Temperature,
    Humidity,
    Pressure,
    SoundLevel,
};

struct Measure {
    std::vector<string> value;
    MeasureKind kind;
    string toJson();
    static Measure fromJson(string);
};

struct CreateMeasures {
    std::vector<Measure> values;
    string toJson();
};

struct MeasureKindMap {
    MeasureKindMap(string, MeasureKind);
    string name;
    MeasureKind kind;
};

const MeasureKindMap measureKindMaps[] = {{"dust", Dust}, {"temperature", Temperature}, {"humidity", Humidity}, {"pressure", Pressure}, {"sound_level", SoundLevel}};
string getMeasureKindName(MeasureKind kind);
tl::optional<Measure> createMeasure(const std::vector<string>& value, const string& kind);
tl::optional<Measure> createMeasure(string value, const string& kind);
tl::optional<MeasureKind> parseMeasureKind(const string& name);
Measure createMeasure(std::vector<string> value, MeasureKind kind);
Measure createMeasure(string value, MeasureKind kind);
CreateMeasures createMeasures(std::vector<Measure> measures);

#endif
