#pragma once

namespace lynq {

enum class ErrorCode {
    Ok = 0,
    Unknown,
    InvalidArgument,
    NotFound,
    AlreadyExists,
    Timeout,
    Busy,
    Cancelled,
    NotConnected,
    AccessDenied,
    OutOfMemory,
    StorageError,
    NetworkError,
    RfError,
    IrError,
    OtaError,
    Unsupported
};

} // namespace lynq
