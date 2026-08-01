#include "lynq/core/Logger.h"
#include "lynq/core/Result.h"
#include "lynq/core/UUID.h"
#include "lynq/core/Version.h"

#include <cassert>
#include <memory>
#include <string>
#include <vector>

namespace {
class MemorySink final : public lynq::LogSink {
public:
    void write(lynq::LogLevel, std::string_view module, std::string_view message) override {
        entries.emplace_back(std::string(module) + ":" + std::string(message));
    }
    std::vector<std::string> entries;
};
}

int main() {
    const auto ok = lynq::Result<int>::success(42);
    assert(ok.ok());
    assert(ok.value() == 42);

    const auto failure = lynq::Result<int>::failure(lynq::ErrorCode::Timeout, "timeout");
    assert(!failure.ok());
    assert(failure.code() == lynq::ErrorCode::Timeout);

    const auto id = lynq::UUID::random();
    const auto text = id.toString();
    const auto parsed = lynq::UUID::parse(text);
    assert(parsed.has_value());
    assert(parsed.value() == id);

    assert(lynq::kSdkVersion.toString() == "0.1.0-alpha");

    lynq::Logger logger;
    auto sink = std::make_shared<MemorySink>();
    logger.addSink(sink);
    logger.info("test", "message");
    assert(sink->entries.size() == 1);
    assert(sink->entries.front() == "test:message");

    return 0;
}
