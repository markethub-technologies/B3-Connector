#pragma once
#include "TopNBookSnapshot.hpp"
#include <string>

namespace b3::md {

// Mapper puro: snapshot -> bytes
// (stub determinístico para tests; luego será Protobuf)
class MdSnapshotMapper {
public:
    void mapAndSerialize(const BookSnapshot& s,
                         std::string& out) const {
        out.clear();
        out.reserve(64);
        out.append("iid=");
        out.append(std::to_string(s.instrumentId));
        out.append(";ts=");
        out.append(std::to_string(s.exchangeTsNs));
        out.append(";bc=");
        out.append(std::to_string(s.bidCount));
        out.append(";ac=");
        out.append(std::to_string(s.askCount));
    }
};

} // namespace b3::md
