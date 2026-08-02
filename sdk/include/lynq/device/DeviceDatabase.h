#pragma once

#include "lynq/core/Result.h"
#include "lynq/device/DeviceCommandBinding.h"

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace lynq::device {

class IDeviceDatabaseStore {
public:
    virtual ~IDeviceDatabaseStore() = default;
    virtual Result<std::string> loadJson() = 0;
    virtual Result<void> saveJson(const std::string& json) = 0;
};

class DeviceDatabase {
public:
    explicit DeviceDatabase(IDeviceDatabaseStore& store);

    Result<void> upsert(DeviceRecord device);
    bool remove(const std::string& deviceId);
    std::optional<DeviceRecord> find(const std::string& deviceId) const;
    std::vector<DeviceRecord> list() const;

    Result<void> load();
    Result<void> save() const;

private:
    IDeviceDatabaseStore& store_;
    std::unordered_map<std::string, DeviceRecord> devices_;
};

} // namespace lynq::device
