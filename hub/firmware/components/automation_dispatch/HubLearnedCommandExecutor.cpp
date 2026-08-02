#include "HubLearnedCommandExecutor.h"

namespace lynq::hub {

Result<void> HubLearnedCommandExecutor::execute(
    const std::string&,
    const std::string&) {
    // Integration point for the existing Hub command router and Node transport.
    return Result<void>::success();
}

} // namespace lynq::hub
