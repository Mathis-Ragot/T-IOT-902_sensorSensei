#include "Measure.h"
#include <utility>

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
