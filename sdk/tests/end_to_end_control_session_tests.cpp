#include "lynq/control/EndToEndControlSession.h"
#include <cassert>
int main(){ using namespace lynq::control; EndToEndControlSession s; assert(s.beginPairing(1)); assert(s.paired("node-1",2)); assert(s.beginCapture("tv","Power",3)); assert(s.captured("cmd-1",4)); assert(s.beginReplay(5)); assert(s.complete(true,"Replay acknowledged",6)); assert(s.snapshot().state==SessionState::Succeeded); assert(s.snapshot().nodeId=="node-1"); return 0; }
