#include "lynq/automation/AutomationScheduler.h"

#include <algorithm>
#include <utility>

namespace lynq::automation {

AutomationScheduler::AutomationScheduler(IAutomationActionExecutor& executor)
    : executor_(executor) {}

Result<void> AutomationScheduler::upsert(AutomationRule rule) {
    if (rule.id.empty() || rule.name.empty() || rule.sceneId.empty()) {
        return Result<void>::failure(
            ErrorCode::InvalidArgument,
            "Automation ID, name and scene ID are required.");
    }

    if (rule.trigger.type == TriggerType::TimeOfDay &&
        (rule.trigger.hour < 0 || rule.trigger.hour > 23 ||
         rule.trigger.minute < 0 || rule.trigger.minute > 59)) {
        return Result<void>::failure(
            ErrorCode::InvalidArgument,
            "Time-of-day trigger is invalid.");
    }

    rules_[rule.id] = std::move(rule);
    return Result<void>::success();
}

bool AutomationScheduler::remove(const std::string& ruleId) {
    return rules_.erase(ruleId) > 0;
}

std::optional<AutomationRule> AutomationScheduler::find(
    const std::string& ruleId) const {
    const auto it = rules_.find(ruleId);
    if (it == rules_.end()) return std::nullopt;
    return it->second;
}

std::vector<AutomationRule> AutomationScheduler::list() const {
    std::vector<AutomationRule> result;
    result.reserve(rules_.size());
    for (const auto& [_, rule] : rules_) result.push_back(rule);
    std::sort(result.begin(), result.end(),
              [](const auto& a, const auto& b) { return a.name < b.name; });
    return result;
}

std::vector<std::string> AutomationScheduler::evaluate(
    const SchedulerContext& context) {
    std::vector<std::string> executed;

    for (auto& [id, rule] : rules_) {
        if (!rule.enabled) continue;
        if (rule.lastRunEpochMinute == context.epochMinute) continue;
        if (!matches(rule, context)) continue;

        const auto result = executor_.activateScene(rule.sceneId);
        if (result.ok()) {
            rule.lastRunEpochMinute = context.epochMinute;
            executed.push_back(id);
        }
    }

    return executed;
}

bool AutomationScheduler::matches(
    const AutomationRule& rule,
    const SchedulerContext& context) const {
    const int minuteOfDay = context.localHour * 60 + context.localMinute;

    switch (rule.trigger.type) {
        case TriggerType::TimeOfDay:
            return context.localHour == rule.trigger.hour &&
                   context.localMinute == rule.trigger.minute;

        case TriggerType::SunriseOffset:
            return context.sunriseMinuteOfDay >= 0 &&
                   minuteOfDay ==
                       context.sunriseMinuteOfDay + rule.trigger.offsetMinutes;

        case TriggerType::SunsetOffset:
            return context.sunsetMinuteOfDay >= 0 &&
                   minuteOfDay ==
                       context.sunsetMinuteOfDay + rule.trigger.offsetMinutes;

        case TriggerType::DeviceEvent:
            return context.eventEndpointId &&
                   context.eventName &&
                   *context.eventEndpointId == rule.trigger.endpointId &&
                   *context.eventName == rule.trigger.eventName;
    }

    return false;
}

} // namespace lynq::automation
