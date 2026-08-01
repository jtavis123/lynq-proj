#include "lynq/device/RoomRegistry.h"

#include <algorithm>
#include <utility>

namespace lynq::device {

Result<void> RoomRegistry::upsert(RoomRecord room) {
    if (room.id.empty() || room.name.empty()) {
        return Result<void>::failure(
            ErrorCode::InvalidArgument,
            "Room ID and name are required.");
    }
    rooms_[room.id] = std::move(room);
    return Result<void>::success();
}

bool RoomRegistry::remove(const std::string& roomId) {
    return rooms_.erase(roomId) > 0;
}

std::optional<RoomRecord> RoomRegistry::find(const std::string& roomId) const {
    const auto it = rooms_.find(roomId);
    if (it == rooms_.end()) return std::nullopt;
    return it->second;
}

std::vector<RoomRecord> RoomRegistry::list() const {
    std::vector<RoomRecord> result;
    result.reserve(rooms_.size());
    for (const auto& [_, room] : rooms_) result.push_back(room);
    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
        if (a.sortOrder != b.sortOrder) return a.sortOrder < b.sortOrder;
        return a.name < b.name;
    });
    return result;
}

} // namespace lynq::device
