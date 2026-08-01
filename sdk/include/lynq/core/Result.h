#pragma once

#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include "lynq/core/ErrorCode.h"

namespace lynq {

template <typename T>
class Result {
public:
    static Result success(T value) {
        return Result(std::move(value), ErrorCode::Ok, {});
    }

    static Result failure(ErrorCode code, std::string message) {
        return Result(std::nullopt, code, std::move(message));
    }

    [[nodiscard]] bool ok() const noexcept { return code_ == ErrorCode::Ok; }
    [[nodiscard]] ErrorCode code() const noexcept { return code_; }
    [[nodiscard]] const std::string& message() const noexcept { return message_; }

    T& value() {
        if (!value_) throw std::logic_error("Result has no value");
        return *value_;
    }

    const T& value() const {
        if (!value_) throw std::logic_error("Result has no value");
        return *value_;
    }

private:
    Result(std::optional<T> value, ErrorCode code, std::string message)
        : value_(std::move(value)), code_(code), message_(std::move(message)) {}

    std::optional<T> value_;
    ErrorCode code_;
    std::string message_;
};

template <>
class Result<void> {
public:
    static Result success() { return Result(ErrorCode::Ok, {}); }
    static Result failure(ErrorCode code, std::string message) {
        return Result(code, std::move(message));
    }
    [[nodiscard]] bool ok() const noexcept { return code_ == ErrorCode::Ok; }
    [[nodiscard]] ErrorCode code() const noexcept { return code_; }
    [[nodiscard]] const std::string& message() const noexcept { return message_; }
private:
    Result(ErrorCode code, std::string message)
        : code_(code), message_(std::move(message)) {}
    ErrorCode code_;
    std::string message_;
};

} // namespace lynq
