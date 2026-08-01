#pragma once

#include "lynq/core/Result.h"

#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace lynq::automation {

enum class TriggerType {
    TimeOfDay,
    SunriseOffset,
    SunsetOffset,
    DeviceEvent
};

struct AutomationTrigger {
    TriggerType type{TriggerType::TimeOfDay};
    int hour{0};
    int minute{0};
    int offsetMinutes{0};
    std::string endpointId;
    std::string eventName;
};

struct AutomationRule {
    std::string id;
    std::string name;
    bool enabled{true};
    std::string sceneId;
    AutomationTrigger trigger;
    std::uint64_t lastRunEpochMinute{0};
};

struct SchedulerContext {
    std::uint64_t epochMinute{0};
    int localHour{0};
    int localMinute{0};
    int sunriseMinuteOfDay{-1};
    int sunsetMinuteOfDay{-1};
    std::optional<std::string> eventEndpointId;
    std::optional<std::string> eventName;
};

class IAutomationActionExecutor {
public:
    virtual ~IAutomationActionExecutor() = default;
    virtual Result<void> activateScene(const std::string& sceneId) = 0;
};

class AutomationScheduler {
public:
    explicit AutomationScheduler(IAutomationActionExecutor& executor);

    Result<void> upsert(AutomationRule rule);
    bool remove(const std::string& ruleId);
    std::optional<AutomationRule> find(const std::string& ruleId) const;
    std::vector<AutomationRule> list() const;

    std::vector<std::string> evaluate(const SchedulerContext& context);

private:
    bool matches(const AutomationRule& rule,
                 const SchedulerContext& context) const;

    IAutomationActionExecutor& executor_;
    std::unordered_map<std::string, AutomationRule> rules_;
};

} // namespace lynq::automation
