#pragma once

#include "lynq/automation/CommandDispatchEngine.h"

namespace lynq::hub {

class HubLearnedCommandExecutor final
    : public automation::ILearnedCommandExecutor {
public:
    Result<void> execute(
        const std::string& nodeId,
        const std::string& learnedCommandId) override;
};

} // namespace lynq::hub
