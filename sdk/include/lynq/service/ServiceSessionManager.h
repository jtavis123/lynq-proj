#pragma once

#include "lynq/core/Result.h"
#include "lynq/service/DeploymentModels.h"

#include <optional>
#include <string>
#include <unordered_map>

namespace lynq::service {

class ServiceSessionManager {
public:
    Result<void> create(ServiceSession session);
    Result<void> revoke(const std::string& sessionId);

    std::optional<ServiceSession> authorize(
        const std::string& sessionId,
        std::uint64_t nowEpochMs) const;

private:
    std::unordered_map<std::string, ServiceSession> sessions_;
};

} // namespace lynq::service
