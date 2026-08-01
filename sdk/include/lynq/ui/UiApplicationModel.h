#pragma once

#include "lynq/core/Result.h"

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace lynq::ui {

enum class PageId {
    Home,
    Rooms,
    Devices,
    Scenes,
    Automations,
    Learn,
    Settings,
    DeviceDetail,
    SceneDetail,
    NodeDetail
};

struct NavigationEntry {
    PageId page{PageId::Home};
    std::string label;
    std::string icon;
    bool primary{false};
};

struct StatusSummary {
    bool wifiConnected{false};
    bool cloudConnected{false};
    bool alexaLinked{false};
    std::uint32_t onlineNodeCount{0};
    std::uint32_t offlineNodeCount{0};
    std::uint32_t activeAlertCount{0};
};

struct HomeTile {
    std::string id;
    std::string title;
    std::string subtitle;
    std::string icon;
    bool enabled{true};
    bool active{false};
    bool warning{false};
};

struct HomeDashboardModel {
    std::string greeting;
    std::string homeName;
    StatusSummary status;
    std::vector<HomeTile> favorites;
    std::vector<HomeTile> scenes;
    std::vector<HomeTile> alerts;
};

struct RouteState {
    PageId page{PageId::Home};
    std::optional<std::string> entityId;
};

class UiApplicationModel {
public:
    UiApplicationModel();

    Result<void> navigate(PageId page,
                          std::optional<std::string> entityId = std::nullopt);
    bool goBack();

    [[nodiscard]] const RouteState& currentRoute() const noexcept;
    [[nodiscard]] const std::vector<NavigationEntry>& primaryNavigation() const noexcept;
    [[nodiscard]] const HomeDashboardModel& home() const noexcept;

    void setHomeModel(HomeDashboardModel model);
    void setStatus(StatusSummary status);

private:
    bool entityRequired(PageId page) const noexcept;

    RouteState current_;
    std::vector<RouteState> history_;
    std::vector<NavigationEntry> primaryNavigation_;
    HomeDashboardModel home_;
};

} // namespace lynq::ui
