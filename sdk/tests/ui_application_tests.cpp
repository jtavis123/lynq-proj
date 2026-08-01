#include "lynq/ui/Theme.h"
#include "lynq/ui/UiApplicationModel.h"

#include <cassert>
#include <string>

int main() {
    using namespace lynq::ui;

    UiApplicationModel app;
    assert(app.currentRoute().page == PageId::Home);
    assert(app.primaryNavigation().size() == 5);

    HomeDashboardModel home;
    home.greeting = "Good evening";
    home.homeName = "Tavis Home";
    home.favorites.push_back({
        "pool-lights", "Pool Lights", "Backyard", "light",
        true, false, false
    });
    home.scenes.push_back({
        "movie-night", "Movie Night", "4 actions", "scene",
        true, false, false
    });
    app.setHomeModel(home);
    assert(app.home().favorites.size() == 1);

    app.setStatus({true, true, true, 3, 1, 1});
    assert(app.home().status.onlineNodeCount == 3);
    assert(app.home().status.activeAlertCount == 1);

    assert(app.navigate(PageId::Devices).ok());
    assert(app.currentRoute().page == PageId::Devices);

    assert(!app.navigate(PageId::DeviceDetail).ok());
    assert(app.navigate(PageId::DeviceDetail, "pool-lights").ok());
    assert(app.currentRoute().entityId.value() == "pool-lights");

    assert(app.goBack());
    assert(app.currentRoute().page == PageId::Devices);
    assert(app.goBack());
    assert(app.currentRoute().page == PageId::Home);

    assert(kLynqDarkTheme.cornerRadius == 18);
    assert(kLynqDarkTheme.accent.blue == 192);
    return 0;
}
