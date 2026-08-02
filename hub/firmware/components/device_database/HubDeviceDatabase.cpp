#include "HubDeviceDatabase.h"

namespace lynq::hub {

HubDeviceDatabaseStore::HubDeviceDatabaseStore(
    storage::JsonConfigurationStore& store)
    : store_(store) {}

Result<std::string> HubDeviceDatabaseStore::loadJson() {
    return store_.load("devices");
}

Result<void> HubDeviceDatabaseStore::saveJson(
    const std::string& json) {
    return store_.save("devices", json);
}

} // namespace lynq::hub
