#pragma once

#include "lynq/core/Result.h"

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace lynq::scene {

struct SceneAction {
    std::string endpointId;
    std::string action;
};

struct SceneRecord {
    std::string id;
    std::string name;
    std::string icon;
    bool alexaExposed{false};
    bool enabled{true};
    std::vector<SceneAction> actions;
};

struct SceneExecutionResult {
    std::size_t completed{0};
    std::size_t failed{0};
};

class ISceneActionExecutor {
public:
    virtual ~ISceneActionExecutor() = default;
    virtual Result<void> execute(const SceneAction& action) = 0;
};

class SceneEngine {
public:
    explicit SceneEngine(ISceneActionExecutor& executor);

    Result<void> upsert(SceneRecord scene);
    bool remove(const std::string& sceneId);
    std::optional<SceneRecord> find(const std::string& sceneId) const;
    std::vector<SceneRecord> list() const;
    Result<SceneExecutionResult> activate(const std::string& sceneId);

private:
    ISceneActionExecutor& executor_;
    std::unordered_map<std::string, SceneRecord> scenes_;
};

} // namespace lynq::scene
