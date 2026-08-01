#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <string_view>
#include <vector>

namespace lynq {

enum class LogLevel { Debug, Info, Warning, Error, Critical };

class LogSink {
public:
    virtual ~LogSink() = default;
    virtual void write(LogLevel level, std::string_view module, std::string_view message) = 0;
};

class Logger {
public:
    void addSink(std::shared_ptr<LogSink> sink);
    void log(LogLevel level, std::string_view module, std::string_view message);

    void debug(std::string_view module, std::string_view message) { log(LogLevel::Debug, module, message); }
    void info(std::string_view module, std::string_view message) { log(LogLevel::Info, module, message); }
    void warning(std::string_view module, std::string_view message) { log(LogLevel::Warning, module, message); }
    void error(std::string_view module, std::string_view message) { log(LogLevel::Error, module, message); }
    void critical(std::string_view module, std::string_view message) { log(LogLevel::Critical, module, message); }

private:
    std::mutex mutex_;
    std::vector<std::shared_ptr<LogSink>> sinks_;
};

} // namespace lynq
