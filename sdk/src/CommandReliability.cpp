#include "lynq/reliability/CommandReliability.h"
#include <algorithm>

namespace lynq::reliability {
CommandReliabilityController::CommandReliabilityController(RetryPolicy policy):policy_(policy){}

ExecutionAudit CommandReliabilityController::begin(const ReliableCommand& c, std::uint64_t now) {
    auto& list=audits_[c.commandId];
    if(!list.empty() && (list.back().state==ExecutionState::Succeeded || list.back().state==ExecutionState::Running)) {
        ExecutionAudit a{c.commandId,ExecutionState::Duplicate,list.back().attempts,"Duplicate command suppressed.",now};
        list.push_back(a); return a;
    }
    if(c.expiresAtEpochMs && c.expiresAtEpochMs<=now) {
        ExecutionAudit a{c.commandId,ExecutionState::Expired,0,"Command expired before execution.",now};
        list.push_back(a); return a;
    }
    expirations_[c.commandId]=c.expiresAtEpochMs;
    std::uint32_t attempts=list.empty()?1:list.back().attempts+1;
    ExecutionAudit a{c.commandId,ExecutionState::Running,attempts,"Execution started.",now};
    list.push_back(a); return a;
}

ExecutionAudit CommandReliabilityController::complete(const std::string& id,bool ok,const std::string& detail,std::uint64_t now){
    auto& list=audits_[id];
    std::uint32_t attempts=list.empty()?0:list.back().attempts;
    ExecutionAudit a{id,ok?ExecutionState::Succeeded:ExecutionState::Failed,attempts,detail,now};
    list.push_back(a); return a;
}

bool CommandReliabilityController::shouldRetry(const std::string& id,std::uint64_t now) const {
    auto it=audits_.find(id); if(it==audits_.end()||it->second.empty()) return false;
    const auto& a=it->second.back();
    auto ex=expirations_.find(id); if(ex!=expirations_.end() && ex->second && ex->second<=now) return false;
    return a.state==ExecutionState::Failed && a.attempts<policy_.maxAttempts;
}

std::uint64_t CommandReliabilityController::nextBackoffMs(const std::string& id) const {
    auto it=audits_.find(id); if(it==audits_.end()||it->second.empty()) return policy_.initialBackoffMs;
    auto attempts=std::max<std::uint32_t>(1,it->second.back().attempts);
    std::uint64_t value=policy_.initialBackoffMs;
    for(std::uint32_t i=1;i<attempts;i++) value=std::min(value*2,policy_.maximumBackoffMs);
    return value;
}

std::optional<ExecutionAudit> CommandReliabilityController::latest(const std::string& id) const {
    auto it=audits_.find(id); if(it==audits_.end()||it->second.empty()) return std::nullopt; return it->second.back();
}
std::vector<ExecutionAudit> CommandReliabilityController::history(const std::string& id) const {
    auto it=audits_.find(id); return it==audits_.end()?std::vector<ExecutionAudit>{}:it->second;
}
} // namespace
