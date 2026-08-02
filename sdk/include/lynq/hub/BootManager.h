#pragma once
#include "lynq/core/Result.h"
#include <functional>
#include <string>
#include <vector>
namespace lynq::hub {
enum class BootStage { PowerOn, Hardware, Storage, Display, Touch, Network, Services, UserInterface, Ready, Failed };
struct BootStep { BootStage stage; std::string label; bool required{true}; std::function<Result<void>()> action; };
struct BootProgress { BootStage stage{BootStage::PowerOn}; std::string label; unsigned completed{0}; unsigned total{0}; bool success{false}; std::string detail; };
class BootManager {
public:
 using ProgressCallback = std::function<void(const BootProgress&)>;
 Result<void> addStep(BootStep step);
 Result<void> run(ProgressCallback progress = {});
 [[nodiscard]] const BootProgress& progress() const noexcept { return progress_; }
private:
 std::vector<BootStep> steps_;
 BootProgress progress_;
};
}
