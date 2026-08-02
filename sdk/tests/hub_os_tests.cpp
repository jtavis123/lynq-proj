#include "lynq/hub/BootManager.h"
#include "lynq/hub/HubSettings.h"
#include <cassert>
#include <vector>
class MemoryStore final : public lynq::hub::IHubSettingsStore {
public:
 lynq::Result<lynq::hub::HubSettings> load() override { return lynq::Result<lynq::hub::HubSettings>::success(value); }
 lynq::Result<void> save(const lynq::hub::HubSettings& v) override { value=v; return lynq::Result<void>::success(); }
 lynq::hub::HubSettings value;
};
int main(){
 using namespace lynq; using namespace lynq::hub;
 BootManager boot; std::vector<BootStage> stages;
 assert(boot.addStep({BootStage::Hardware,"Hardware",true,[]{return Result<void>::success();}}).ok());
 assert(boot.addStep({BootStage::Display,"Display",true,[]{return Result<void>::success();}}).ok());
 assert(boot.run([&](const BootProgress&p){stages.push_back(p.stage);}).ok());
 assert(boot.progress().stage==BootStage::Ready); assert(boot.progress().completed==2);
 MemoryStore store; HubSettingsService settings(store); assert(settings.initialize().ok());
 auto next=settings.current(); next.hubName="Kitchen Hub"; next.brightnessPercent=65; assert(settings.update(next).ok()); assert(settings.current().hubName=="Kitchen Hub");
 next.brightnessPercent=101; assert(!settings.update(next).ok()); return 0;
}
