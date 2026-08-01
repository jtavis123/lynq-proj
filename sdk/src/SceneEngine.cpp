#include "lynq/scene/SceneEngine.h"

#include <algorithm>
#include <utility>

namespace lynq::scene {

SceneEngine::SceneEngine(ISceneActionExecutor& executor) : executor_(executor) {}

Result<void> SceneEngine::upsert(SceneRecord scene) {
    if (scene.id.empty() || scene.name.empty() || scene.actions.empty()) {
        return Result<void>::failure(
            ErrorCode::InvalidArgument,
            "Scene ID, name and at least one action are required.");
    }
    scenes_[scene.id] = std::move(scene);
    return Result<void>::success();
}

bool SceneEngine::remove(const std::string& sceneId) {
    return scenes_.erase(sceneId) > 0;
}

std::optional<SceneRecord> SceneEngine::find(const std::string& sceneId) const {
    const auto it = scenes_.find(sceneId);
    if (it == scenes_.end()) return std::nullopt;
    return it->second;
}

std::vector<SceneRecord> SceneEngine::list() const {
    std::vector<SceneRecord> result;
    result.reserve(scenes_.size());
    for (const auto& [_, scene] : scenes_) result.push_back(scene);
    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
        return a.name < b.name;
    });
    return result;
}

Result<SceneExecutionResult> SceneEngine::activate(const std::string& sceneId) {
    const auto scene = find(sceneId);
    if (!scene) {
        return Result<SceneExecutionResult>::failure(
            ErrorCode::NotFound, "Scene was not found.");
    }
    if (!scene->enabled) {
        return Result<SceneExecutionResult>::failure(
            ErrorCode::AccessDenied, "Scene is disabled.");
    }

    SceneExecutionResult summary;
    for (const auto& action : scene->actions) {
        const auto result = executor_.execute(action);
        if (result.ok()) ++summary.completed;
        else ++summary.failed;
    }
    return Result<SceneExecutionResult>::success(summary);
}

} // namespace lynq::scene
