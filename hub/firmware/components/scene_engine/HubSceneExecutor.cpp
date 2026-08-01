#include "HubSceneExecutor.h"

namespace lynq::hub {

HubSceneActionExecutor::HubSceneActionExecutor(command::CommandRouter& router)
    : router_(router) {}

Result<void> HubSceneActionExecutor::execute(const scene::SceneAction& action) {
    command::CommandRequest request;
    request.commandId = "scene:" + action.endpointId + ":" + action.action;
    request.endpointId = action.endpointId;
    request.action = action.action;
    request.source = command::CommandSource::Automation;

    const auto result = router_.route(request, 0);
    if (!result.success) {
        return Result<void>::failure(ErrorCode::Unknown, result.detail);
    }
    return Result<void>::success();
}

} // namespace lynq::hub
