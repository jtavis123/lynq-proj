#include "lynq/hub/BootManager.h"
#include <utility>
namespace lynq::hub {
Result<void> BootManager::addStep(BootStep step) {
 if (step.label.empty() || !step.action) return Result<void>::failure(ErrorCode::InvalidArgument, "Boot step requires a label and action.");
 steps_.push_back(std::move(step)); return Result<void>::success();
}
Result<void> BootManager::run(ProgressCallback callback) {
 progress_ = {}; progress_.total = static_cast<unsigned>(steps_.size());
 for (const auto& step : steps_) {
  progress_.stage = step.stage; progress_.label = step.label; progress_.success = false; progress_.detail.clear();
  if (callback) callback(progress_);
  const auto result = step.action();
  if (!result.ok()) {
   progress_.detail = result.message();
   if (step.required) { progress_.stage = BootStage::Failed; if (callback) callback(progress_); return result; }
  }
  ++progress_.completed; progress_.success = result.ok(); if (callback) callback(progress_);
 }
 progress_.stage = BootStage::Ready; progress_.label = "LYNQ Hub ready"; progress_.success = true;
 if (callback) callback(progress_); return Result<void>::success();
}
}
