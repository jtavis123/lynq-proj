#pragma once

#include "lynq/ui/UiApplicationModel.h"

namespace lynq::hub {

class HubUiController {
public:
    explicit HubUiController(ui::UiApplicationModel& model);

    bool initialize();
    void render();
    void onPrimaryNavigation(ui::PageId page);
    void onBack();

private:
    ui::UiApplicationModel& model_;
    bool initialized_{false};
};

} // namespace lynq::hub
