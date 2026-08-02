#include "lynq/reliability/SystemHealthScore.h"
namespace lynq::reliability {
HealthScore SystemHealthScore::calculate(const HealthInput& i){
    int score=100; HealthScore out;
    if(!i.wifi){score-=30;out.issues.push_back("Wi-Fi disconnected");}
    if(!i.cloud){score-=10;out.issues.push_back("Cloud unavailable");}
    if(i.offlineNodes){score-=static_cast<int>(i.offlineNodes)*15;out.issues.push_back("One or more Nodes offline");}
    if(!i.storageHealthy){score-=30;out.issues.push_back("Storage health check failed");}
    if(!i.otaHealthy){score-=15;out.issues.push_back("OTA subsystem degraded");}
    if(score<0) score=0; out.score=static_cast<std::uint32_t>(score);
    out.label=score>=90?"Excellent":score>=75?"Good":score>=50?"Degraded":"Critical";
    return out;
}
}
