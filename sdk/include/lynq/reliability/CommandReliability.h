#pragma once
#include <cstdint>
#include <deque>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace lynq::reliability {

enum class ExecutionState { Pending, Running, Succeeded, Failed, Expired, Duplicate };

struct RetryPolicy {
    std::uint32_t maxAttempts{3};
    std::uint64_t initialBackoffMs{250};
    std::uint64_t maximumBackoffMs{4000};
};

struct ReliableCommand {
    std::string commandId;
    std::string deviceId;
    std::string commandName;
    std::uint64_t createdAtEpochMs{0};
    std::uint64_t expiresAtEpochMs{0};
};

struct ExecutionAudit {
    std::string commandId;
    ExecutionState state{ExecutionState::Pending};
    std::uint32_t attempts{0};
    std::string detail;
    std::uint64_t timestampEpochMs{0};
};

class CommandReliabilityController {
public:
    explicit CommandReliabilityController(RetryPolicy policy = {});
    ExecutionAudit begin(const ReliableCommand& command, std::uint64_t nowEpochMs);
    ExecutionAudit complete(const std::string& commandId, bool success,
                            const std::string& detail, std::uint64_t nowEpochMs);
    bool shouldRetry(const std::string& commandId, std::uint64_t nowEpochMs) const;
    std::uint64_t nextBackoffMs(const std::string& commandId) const;
    std::optional<ExecutionAudit> latest(const std::string& commandId) const;
    std::vector<ExecutionAudit> history(const std::string& commandId) const;
private:
    RetryPolicy policy_;
    std::unordered_map<std::string,std::vector<ExecutionAudit>> audits_;
    std::unordered_map<std::string,std::uint64_t> expirations_;
};

} // namespace lynq::reliability
