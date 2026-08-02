#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace lynq::ui {
struct DashboardDevice { std::string deviceId,name,room,category; bool favorite{false},available{true},active{false}; };
struct DashboardScene { std::string sceneId,name,subtitle; bool favorite{false}; };
struct DashboardAutomation { std::string automationId,name,trigger; bool enabled{true}; };
struct DashboardActivity { std::string activityId,source,title,detail; bool success{true}; std::uint64_t timestampEpochMs{0}; };
struct DashboardConnection { bool wifiConnected{false},cloudConnected{false},alexaLinked{false}; std::uint32_t onlineNodes{0},offlineNodes{0}; };
struct HubDashboardInput { std::string hubName; DashboardConnection connection; std::vector<DashboardDevice> devices; std::vector<DashboardScene> scenes; std::vector<DashboardAutomation> automations; std::vector<DashboardActivity> activity; };
struct HubDashboardView { std::string title,connectionMessage; bool showOfflineBanner{false},showOnboarding{false}; std::vector<DashboardDevice> favoriteDevices; std::vector<DashboardScene> favoriteScenes; std::vector<DashboardAutomation> activeAutomations; std::vector<DashboardActivity> recentActivity; };
class HubDashboardComposer { public: static HubDashboardView compose(const HubDashboardInput&,std::size_t deviceLimit=4,std::size_t sceneLimit=3,std::size_t activityLimit=5); };
}
