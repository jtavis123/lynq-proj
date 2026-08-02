#pragma once
#include "lynq/learning/LearningWizard.h"
#include "lynq/ui/UiApplicationModel.h"

namespace lynq::hub {
class HubLearningWizard {
public:
    HubLearningWizard(learning::LearningWizard& wizard,
                      ui::UiApplicationModel& uiModel)
        : wizard_(wizard), uiModel_(uiModel) {}
    Result<void> open();
    Result<void> selectDevice(const std::string& deviceId);
    Result<void> selectNode(const std::string& nodeId,
                            learning::SignalTransport transport);
    Result<void> capture();
    Result<void> test();
    Result<learning::LearnedCommand> save(const std::string& name,
                                           std::uint64_t nowEpochMs);
private:
    learning::LearningWizard& wizard_;
    ui::UiApplicationModel& uiModel_;
};
}
