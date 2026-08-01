#pragma once

#include "lynq/core/Result.h"

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace lynq::device {

struct RoomRecord {
    std::string id;
    std::string name;
    std::string icon;
    int sortOrder{0};
};

class RoomRegistry {
public:
    Result<void> upsert(RoomRecord room);
    bool remove(const std::string& roomId);
    std::optional<RoomRecord> find(const std::string& roomId) const;
    std::vector<RoomRecord> list() const;

private:
    std::unordered_map<std::string, RoomRecord> rooms_;
};

} // namespace lynq::device
