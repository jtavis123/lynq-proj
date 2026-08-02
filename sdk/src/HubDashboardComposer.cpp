#include "lynq/ui/HubDashboardComposer.h"
#include <algorithm>
namespace lynq::ui {
HubDashboardView HubDashboardComposer::compose(const HubDashboardInput& in,std::size_t dl,std::size_t sl,std::size_t al){
 HubDashboardView v; v.title=in.hubName.empty()?"LYNQ Home":in.hubName; v.showOnboarding=in.devices.empty();
 if(!in.connection.wifiConnected){v.connectionMessage="Wi-Fi disconnected";v.showOfflineBanner=true;}
 else if(!in.connection.cloudConnected){v.connectionMessage="Local control available";v.showOfflineBanner=true;}
 else if(in.connection.offlineNodes>0){v.connectionMessage=std::to_string(in.connection.offlineNodes)+" Node offline";v.showOfflineBanner=true;}
 else v.connectionMessage="All systems online";
 for(const auto& d:in.devices) if(d.favorite&&v.favoriteDevices.size()<dl) v.favoriteDevices.push_back(d);
 for(const auto& s:in.scenes) if(s.favorite&&v.favoriteScenes.size()<sl) v.favoriteScenes.push_back(s);
 for(const auto& a:in.automations) if(a.enabled) v.activeAutomations.push_back(a);
 v.recentActivity=in.activity; std::sort(v.recentActivity.begin(),v.recentActivity.end(),[](auto&a,auto&b){return a.timestampEpochMs>b.timestampEpochMs;});
 if(v.recentActivity.size()>al) v.recentActivity.resize(al); return v;
}
}
