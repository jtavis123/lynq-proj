#pragma once

#include "lynq/device/DeviceRegistry.h"
#include "lynq/device/RoomRegistry.h"
#include "lynq/storage/IConfigurationStore.h"

namespace lynq::hub {

class HubDeviceRegistry {
public:
    HubDeviceRegistry(device::DeviceRegistry& devices,
                      device::RoomRegistry& rooms,
                      storage::IConfigurationStore& store);

    Result<void> load();
    Result<void> save();

private:
    device::DeviceRegistry& devices_;
    device::RoomRegistry& rooms_;
    storage::IConfigurationStore& store_;
};

} // namespace lynq::hub
