#pragma once
#include "lynq/cloud/CloudModels.h"
#include "lynq/core/Result.h"
#include <cstdint>
#include <string>
#include <vector>
namespace lynq::alexa {
struct EndpointCommand { std::string name; bool enabled{true}; };
struct EndpointRecord { std::string deviceId,name,roomId,category; bool enabled{true}; std::vector<EndpointCommand> commands; };
struct AlexaEndpoint { std::string endpointId,friendlyName,displayCategory; std::vector<std::string> capabilities; };
struct AlexaDirective { std::string messageId,householdId,hubId,endpointId,directiveName; std::uint64_t expiresAtEpochMs{0}; };
class AlexaBridge {
public:
 explicit AlexaBridge(std::vector<EndpointRecord> endpoints):endpoints_(std::move(endpoints)){}
 std::vector<AlexaEndpoint> discover() const;
 Result<cloud::RemoteCommand> translate(const AlexaDirective& d,std::uint64_t now) const;
private: std::vector<EndpointRecord> endpoints_;
};
}
