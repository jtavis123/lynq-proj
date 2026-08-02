#include "lynq/control/EndToEndControlSession.h"
#include <utility>
namespace lynq::control {
bool EndToEndControlSession::beginPairing(std::uint64_t now){ if(snapshot_.state!=SessionState::Idle&&snapshot_.state!=SessionState::Failed) return false; snapshot_={}; snapshot_.state=SessionState::Pairing; snapshot_.updatedAtMs=now; return true; }
bool EndToEndControlSession::paired(std::string nodeId,std::uint64_t now){ if(snapshot_.state!=SessionState::Pairing||nodeId.empty()) return false; snapshot_.nodeId=std::move(nodeId); snapshot_.state=SessionState::Ready; snapshot_.updatedAtMs=now; return true; }
bool EndToEndControlSession::beginCapture(std::string deviceId,std::string commandName,std::uint64_t now){ if(snapshot_.state!=SessionState::Ready||deviceId.empty()||commandName.empty()) return false; snapshot_.deviceId=std::move(deviceId); snapshot_.commandName=std::move(commandName); snapshot_.state=SessionState::Capturing; snapshot_.updatedAtMs=now; return true; }
bool EndToEndControlSession::captured(std::string learnedCommandId,std::uint64_t now){ if(snapshot_.state!=SessionState::Capturing||learnedCommandId.empty()) return false; snapshot_.learnedCommandId=std::move(learnedCommandId); snapshot_.state=SessionState::Captured; snapshot_.updatedAtMs=now; return true; }
bool EndToEndControlSession::beginReplay(std::uint64_t now){ if(snapshot_.state!=SessionState::Captured) return false; snapshot_.state=SessionState::Replaying; snapshot_.updatedAtMs=now; return true; }
bool EndToEndControlSession::complete(bool success,std::string detail,std::uint64_t now){ if(snapshot_.state!=SessionState::Replaying) return false; snapshot_.state=success?SessionState::Succeeded:SessionState::Failed; snapshot_.detail=std::move(detail); snapshot_.updatedAtMs=now; return true; }
}
