#pragma once
#include <cstdint>
#include <string>
namespace lynq::cloud {
struct RegisteredHub { std::string hubId, householdId, displayName, firmwareVersion; bool online{false}; std::uint64_t lastSeenEpochMs{0}; };
struct RemoteCommand { std::string commandId, householdId, hubId, deviceId, commandName; std::uint64_t createdAtEpochMs{0}, expiresAtEpochMs{0}; };
enum class CommandAckState { Accepted, Executing, Succeeded, Failed, Expired, Rejected };
struct CommandAcknowledgement { std::string commandId, hubId; CommandAckState state{CommandAckState::Accepted}; std::string detail; std::uint64_t timestampEpochMs{0}; };
struct ActivityRecord { std::string activityId, householdId, hubId, source, deviceId, commandName; bool success{false}; std::string detail; std::uint64_t timestampEpochMs{0}; };
}
