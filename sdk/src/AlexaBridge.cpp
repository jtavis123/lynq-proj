#include "lynq/alexa/AlexaBridge.h"
namespace lynq::alexa {
std::vector<AlexaEndpoint> AlexaBridge::discover() const { std::vector<AlexaEndpoint> out; for(const auto& d:endpoints_){ if(!d.enabled) continue; AlexaEndpoint e{d.deviceId,d.name,d.category=="television"?"TV":d.category=="light"?"LIGHT":"OTHER",{}}; for(const auto& c:d.commands) if(c.enabled) e.capabilities.push_back(c.name); out.push_back(e);} return out; }
Result<cloud::RemoteCommand> AlexaBridge::translate(const AlexaDirective& d,std::uint64_t now) const {
 std::string command=d.directiveName=="TurnOn"?"Power On":d.directiveName=="TurnOff"?"Power Off":d.directiveName;
 for(const auto& e:endpoints_) if(e.deviceId==d.endpointId&&e.enabled){ bool ok=false; for(const auto& c:e.commands) if(c.enabled&&c.name==command) ok=true; if(!ok) return Result<cloud::RemoteCommand>::failure(ErrorCode::Unsupported,"Directive unsupported."); return Result<cloud::RemoteCommand>::success({"alexa-"+d.messageId,d.householdId,d.hubId,d.endpointId,command,now,d.expiresAtEpochMs}); }
 return Result<cloud::RemoteCommand>::failure(ErrorCode::NotFound,"Endpoint unavailable.");
}
}
