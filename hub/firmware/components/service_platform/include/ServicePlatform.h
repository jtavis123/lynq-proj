#pragma once

#include "lynq/service/DeploymentModels.h"

#include <string>
#include <vector>

namespace lynq::hub {

class IServicePlatform {
public:
    virtual ~IServicePlatform() = default;

    virtual bool createConfigurationBackup(
        const std::string& destinationPath) = 0;

    virtual bool restoreConfigurationBackup(
        const std::string& sourcePath) = 0;

    virtual bool scheduleHubUpdate(
        const service::UpdatePlan& plan) = 0;

    virtual bool scheduleNodeUpdate(
        const service::UpdatePlan& plan) = 0;

    virtual std::vector<service::CrashRecord>
        recentCrashes() const = 0;
};

} // namespace lynq::hub
