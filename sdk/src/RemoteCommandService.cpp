#include "lynq/cloud/RemoteCommandService.h"
#include <utility>
namespace lynq::cloud {
Result<void> RemoteCommandService::registerHub(RegisteredHub hub){
 if(hub.hubId.empty()||hub.householdId.empty()) return Result<void>::failure(ErrorCode::InvalidArgument,"Hub registration incomplete.");
 hubs_[hub.hubId]=std::move(hub); return Result<void>::success();
}
Result<void> RemoteCommandService::setHubOnline(const std::string& id,bool online,std::uint64_t now){
 auto it=hubs_.find(id); if(it==hubs_.end()) return Result<void>::failure(ErrorCode::NotFound,"Hub not registered.");
 it->second.online=online; it->second.lastSeenEpochMs=now; return Result<void>::success();
}
Result<void> RemoteCommandService::enqueue(RemoteCommand c){
 auto it=hubs_.find(c.hubId); if(it==hubs_.end()) return Result<void>::failure(ErrorCode::NotFound,"Hub not registered.");
 if(it->second.householdId!=c.householdId) return Result<void>::failure(ErrorCode::Unauthorized,"Household mismatch.");
 if(c.commandId.empty()||c.deviceId.empty()||c.commandName.empty()) return Result<void>::failure(ErrorCode::InvalidArgument,"Command incomplete.");
 queue_.push_back(std::move(c)); return Result<void>::success();
}
std::optional<RemoteCommand> RemoteCommandService::nextForHub(const std::string& id,std::uint64_t now){
 auto h=hubs_.find(id); if(h==hubs_.end()||!h->second.online) return std::nullopt;
 for(auto it=queue_.begin();it!=queue_.end();){
  if(it->expiresAtEpochMs&&it->expiresAtEpochMs<=now){ acks_[it->commandId].push_back({it->commandId,it->hubId,CommandAckState::Expired,"Expired before delivery.",now}); it=queue_.erase(it); continue; }
  if(it->hubId==id){ auto c=*it; queue_.erase(it); acks_[c.commandId].push_back({c.commandId,c.hubId,CommandAckState::Accepted,"Delivered to Hub.",now}); return c; }
  ++it;
 }
 return std::nullopt;
}
Result<void> RemoteCommandService::acknowledge(CommandAcknowledgement a){ if(a.commandId.empty()||a.hubId.empty()) return Result<void>::failure(ErrorCode::InvalidArgument,"Ack incomplete."); acks_[a.commandId].push_back(std::move(a)); return Result<void>::success(); }
std::vector<CommandAcknowledgement> RemoteCommandService::acknowledgements(const std::string& id) const { auto it=acks_.find(id); return it==acks_.end()?std::vector<CommandAcknowledgement>{}:it->second; }
}
