#include "lynq/ui/UiApplicationModel.h"

#include <utility>

namespace lynq::ui {

UiApplicationModel::UiApplicationModel()
    : primaryNavigation_({
          {PageId::Home, "Home", "home", true},
          {PageId::Devices, "Devices", "devices", true},
          {PageId::Scenes, "Scenes", "scenes", true},
          {PageId::Automations, "Automations", "automation", true},
          {PageId::Settings, "Settings", "settings", true}
      }) {
    home_.greeting = "Welcome home";
    home_.homeName = "My Home";
}

Result<void> UiApplicationModel::navigate(
    PageId page,
    std::optional<std::string> entityId) {
    if (entityRequired(page) && (!entityId || entityId->empty())) {
        return Result<void>::failure(
            ErrorCode::InvalidArgument,
            "The selected detail page requires an entity ID.");
    }

    if (current_.page == page && current_.entityId == entityId) {
        return Result<void>::success();
    }

    history_.push_back(current_);
    current_ = {page, std::move(entityId)};
    return Result<void>::success();
}

bool UiApplicationModel::goBack() {
    if (history_.empty()) return false;
    current_ = history_.back();
    history_.pop_back();
    return true;
}

const RouteState& UiApplicationModel::currentRoute() const noexcept {
    return current_;
}

const std::vector<NavigationEntry>&
UiApplicationModel::primaryNavigation() const noexcept {
    return primaryNavigation_;
}

const HomeDashboardModel& UiApplicationModel::home() const noexcept {
    return home_;
}

void UiApplicationModel::setHomeModel(HomeDashboardModel model) {
    home_ = std::move(model);
}

void UiApplicationModel::setStatus(StatusSummary status) {
    home_.status = status;
}

bool UiApplicationModel::entityRequired(PageId page) const noexcept {
    return page == PageId::DeviceDetail ||
           page == PageId::SceneDetail ||
           page == PageId::NodeDetail;
}

} // namespace lynq::ui
