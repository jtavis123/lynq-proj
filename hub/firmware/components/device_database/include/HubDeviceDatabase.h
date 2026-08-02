#pragma once

#include "lynq/device/DeviceDatabase.h"
#include "lynq/storage/JsonConfigurationStore.h"

namespace lynq::hub {

class HubDeviceDatabaseStore final
    : public device::IDeviceDatabaseStore {
public:
    explicit HubDeviceDatabaseStore(
        storage::JsonConfigurationStore& store);

    Result<std::string> loadJson() override;
    Result<void> saveJson(const std::string& json) override;

private:
    storage::JsonConfigurationStore& store_;
};

} // namespace lynq::hub
