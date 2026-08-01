#pragma once

#include "lynq/ui/Theme.h"
#include "lynq/ui/UiApplicationModel.h"

namespace lynq::hub {

class LvglUiPort {
public:
    bool initialize();
    void buildApplicationShell(const ui::UiApplicationModel& model);
    void refreshHome(const ui::HomeDashboardModel& home);

private:
    bool ready_{false};
};

} // namespace lynq::hub
