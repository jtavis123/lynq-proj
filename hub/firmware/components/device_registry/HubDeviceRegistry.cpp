#include "HubDeviceRegistry.h"

namespace lynq::hub {

HubDeviceRegistry::HubDeviceRegistry(device::DeviceRegistry& devices,
                                     device::RoomRegistry& rooms,
                                     storage::IConfigurationStore& store)
    : devices_(devices), rooms_(rooms), store_(store) {}

Result<void> HubDeviceRegistry::load() {
    // Serialization is connected after the ESP-IDF JSON/NVS adapter is selected.
    return Result<void>::success();
}

Result<void> HubDeviceRegistry::save() {
    // The persistent schema is versioned before production data is written.
    return Result<void>::success();
}

} // namespace lynq::hub
