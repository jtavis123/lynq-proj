#pragma once
#include <string>
namespace lynq::node {
class IReplayDriver { public: virtual ~IReplayDriver()=default; virtual bool replay(const std::string& learnedCommandId)=0; };
struct ReplayAcknowledgement { std::string requestId; bool success{false}; std::string detail; };
class ControlEndpoint { public: explicit ControlEndpoint(IReplayDriver& d):driver_(d){} ReplayAcknowledgement execute(const std::string& requestId,const std::string& learnedCommandId){ if(requestId.empty()||learnedCommandId.empty()) return {requestId,false,"Invalid replay request"}; const bool ok=driver_.replay(learnedCommandId); return {requestId,ok,ok?"Replay completed":"Replay failed"}; } private:IReplayDriver& driver_; };
}
