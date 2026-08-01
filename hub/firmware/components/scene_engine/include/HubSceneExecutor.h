#pragma once

#include "lynq/command/CommandRouter.h"
#include "lynq/scene/SceneEngine.h"

namespace lynq::hub {

class HubSceneActionExecutor final : public scene::ISceneActionExecutor {
public:
    explicit HubSceneActionExecutor(command::CommandRouter& router);
    Result<void> execute(const scene::SceneAction& action) override;

private:
    command::CommandRouter& router_;
};

} // namespace lynq::hub
