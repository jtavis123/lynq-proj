#pragma once
#include "lynq/cloud/CloudModels.h"
#include "lynq/core/Result.h"
#include <deque>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
namespace lynq::cloud {
class RemoteCommandService {
public:
 Result<void> registerHub(RegisteredHub hub);
 Result<void> setHubOnline(const std::string& hubId,bool online,std::uint64_t now);
 Result<void> enqueue(RemoteCommand command);
 std::optional<RemoteCommand> nextForHub(const std::string& hubId,std::uint64_t now);
 Result<void> acknowledge(CommandAcknowledgement ack);
 std::vector<CommandAcknowledgement> acknowledgements(const std::string& commandId) const;
private:
 std::unordered_map<std::string,RegisteredHub> hubs_;
 std::deque<RemoteCommand> queue_;
 std::unordered_map<std::string,std::vector<CommandAcknowledgement>> acks_;
};
}
