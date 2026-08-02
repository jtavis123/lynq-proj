#pragma once
#include <cstdint>
#include <string>
namespace lynq::control {
enum class SessionState { Idle, Pairing, Ready, Capturing, Captured, Replaying, Succeeded, Failed };
struct SessionSnapshot { SessionState state{SessionState::Idle}; std::string nodeId; std::string deviceId; std::string commandName; std::string learnedCommandId; std::string detail; std::uint64_t updatedAtMs{0}; };
class EndToEndControlSession {
public:
 bool beginPairing(std::uint64_t now); bool paired(std::string nodeId,std::uint64_t now);
 bool beginCapture(std::string deviceId,std::string commandName,std::uint64_t now);
 bool captured(std::string learnedCommandId,std::uint64_t now);
 bool beginReplay(std::uint64_t now); bool complete(bool success,std::string detail,std::uint64_t now);
 const SessionSnapshot& snapshot() const { return snapshot_; }
private: SessionSnapshot snapshot_;
};
}
