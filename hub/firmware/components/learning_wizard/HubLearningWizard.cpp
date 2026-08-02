#include "HubLearningWizard.h"
namespace lynq::hub {
Result<void> HubLearningWizard::open() { wizard_.reset(); return uiModel_.navigate(ui::PageId::Learn); }
Result<void> HubLearningWizard::selectDevice(const std::string& id) { return wizard_.selectDevice(id); }
Result<void> HubLearningWizard::selectNode(const std::string& id, learning::SignalTransport t) { return wizard_.selectNode(id, t); }
Result<void> HubLearningWizard::capture() { return wizard_.beginCapture(); }
Result<void> HubLearningWizard::test() { return wizard_.testReplay(); }
Result<learning::LearnedCommand> HubLearningWizard::save(const std::string& name, std::uint64_t now) {
    auto named = wizard_.setCommandName(name);
    if (!named.ok()) return Result<learning::LearnedCommand>::failure(named.code(), named.message());
    return wizard_.save(now);
}
}
