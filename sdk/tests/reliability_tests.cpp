#include "lynq/reliability/CommandReliability.h"
#include "lynq/reliability/SystemHealthScore.h"
#include <cassert>
int main(){
 using namespace lynq::reliability;
 CommandReliabilityController c({3,100,1000});
 ReliableCommand cmd{"cmd-1","tv","Power",1000,5000};
 auto first=c.begin(cmd,1100); assert(first.state==ExecutionState::Running&&first.attempts==1);
 auto dup=c.begin(cmd,1150); assert(dup.state==ExecutionState::Duplicate);
 c.complete("cmd-1",false,"timeout",1200); assert(c.shouldRetry("cmd-1",1300)); assert(c.nextBackoffMs("cmd-1")==100);
 auto retry=c.begin(cmd,1400); assert(retry.attempts==2); c.complete("cmd-1",true,"ok",1500); assert(!c.shouldRetry("cmd-1",1600));
 auto h=SystemHealthScore::calculate({true,false,1,1,true,true}); assert(h.score==75); assert(h.label=="Good");
 return 0;
}
