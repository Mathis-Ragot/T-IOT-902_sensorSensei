#include "Measure.h"

MeasureKindMap::MeasureKindMap(String name, MeasureKind kind) {
    this->kind = kind;
    this->name = std::move(name);
}

std::optional<Measure> createMeasure(const std::vector<String>& value, const String& kind) {
    for (const auto &item: measureKindMaps) {
        if (kind.equalsIgnoreCase(item.name)) {
            return std::optional(Measure {
                    value,
                    item.kind
            });
        }
    }
    return std::nullopt;
}

std::optional<MeasureKind> parseMeasureKind(const String& name) {
    for (const auto &item: measureKindMaps) {
        if (item.name.equalsIgnoreCase(name)) {
            return item.kind;
        }
    }
    return std::nullopt;
}

String getMeasureKindName(MeasureKind kind){
    for (const auto &item: measureKindMaps) {
        if (item.kind == kind) {
            return item.name;
        }
    }
    throw std::invalid_argument("Invalid MeasureKind");
}

std::optional<Measure> createMeasure(String value, const String& kind) {
    if (parseMeasureKind(kind).has_value()) {
        return std::optional(Measure {
                std::vector<String>{std::move(value)},
                parseMeasureKind(kind).value()
        });
    }
    return std::nullopt;
}

Measure createMeasure(std::vector<String> value, MeasureKind kind) {
    return Measure {
            std::move(value),
            kind
    };
}

Measure createMeasure(String value, MeasureKind kind) {
    return Measure {
            std::vector<String>{std::move(value)},
            kind
    };
}


CreateMeasures createMeasures(std::vector<Measure> measures) {
    return CreateMeasures {
            std::move(measures)
    };
}

String Measure::toJson()  {
    JsonDocument doc;
    String s;
    doc["kind"] = getMeasureKindName(this->kind);
    for (int i = 0; i < this->value.size(); i++) {
        doc["value"][i] = this->value[i];
    }
    serializeJson(doc, s);
    return s;
}

Measure Measure::fromJson(String data) {
    JsonDocument doc;
    deserializeJson(doc, data);
    return Measure {
        .value = {doc["data"][0], doc["data"][1]},
        .kind =  parseMeasureKind(doc["kind"]).value()
    };
}

String CreateMeasures::toJson() {
    JsonDocument doc;
    String s;
    for (int i = 0; i < this->values.size(); i++) {
        doc["values"][i]["kind"] = getMeasureKindName(this->values[i].kind);
        for (int j = 0; j < this->values[i].value.size(); j++) {
            doc["values"][i]["value"][j] = this->values[i].value[j];
        }
    }
    serializeJson(doc, s);
    return s;
}
