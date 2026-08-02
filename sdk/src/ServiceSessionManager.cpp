#include "lynq/service/ServiceSessionManager.h"

#include <utility>

namespace lynq::service {

Result<void> ServiceSessionManager::create(
    ServiceSession session) {
    if (session.sessionId.empty() ||
        session.technicianId.empty() ||
        session.expiresAtEpochMs <= session.issuedAtEpochMs) {
        return Result<void>::failure(
            ErrorCode::InvalidArgument,
            "Service session is invalid.");
    }

    sessions_[session.sessionId] = std::move(session);
    return Result<void>::success();
}

Result<void> ServiceSessionManager::revoke(
    const std::string& sessionId) {
    if (sessions_.erase(sessionId) == 0) {
        return Result<void>::failure(
            ErrorCode::NotFound,
            "Service session was not found.");
    }
    return Result<void>::success();
}

std::optional<ServiceSession>
ServiceSessionManager::authorize(
    const std::string& sessionId,
    std::uint64_t nowEpochMs) const {
    const auto it = sessions_.find(sessionId);
    if (it == sessions_.end() ||
        it->second.expiresAtEpochMs <= nowEpochMs) {
        return std::nullopt;
    }
    return it->second;
}

} // namespace lynq::service
