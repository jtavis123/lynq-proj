#include "lynq/core/Logger.h"

namespace lynq {

void Logger::addSink(std::shared_ptr<LogSink> sink) {
    if (!sink) return;
    std::scoped_lock lock(mutex_);
    sinks_.push_back(std::move(sink));
}

void Logger::log(LogLevel level, std::string_view module, std::string_view message) {
    std::vector<std::shared_ptr<LogSink>> sinks;
    {
        std::scoped_lock lock(mutex_);
        sinks = sinks_;
    }
    for (const auto& sink : sinks) {
        sink->write(level, module, message);
    }
}

} // namespace lynq
