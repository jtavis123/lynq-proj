#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace lynq::service {

enum class UpdateTarget {
    Hub,
    Node
};

enum class UpdateState {
    Idle,
    Checking,
    Downloading,
    Verifying,
    Installing,
    AwaitingHealthCheck,
    Completed,
    RolledBack,
    Failed
};

struct FirmwareArtifact {
    std::string artifactId;
    UpdateTarget target{UpdateTarget::Hub};
    std::string hardwareProfile;
    std::string version;
    std::string downloadPath;
    std::string sha256;
    std::string signature;
    std::uint64_t sizeBytes{0};
};

struct UpdatePlan {
    std::string planId;
    FirmwareArtifact artifact;
    std::vector<std::string> nodeIds;
    bool allowDowngrade{false};
    bool requireExternalPower{true};
};

struct UpdateStatus {
    std::string planId;
    UpdateState state{UpdateState::Idle};
    std::uint32_t progressPercent{0};
    std::string detail;
};

struct BackupManifest {
    std::uint32_t schemaVersion{1};
    std::string backupId;
    std::string hubId;
    std::string firmwareVersion;
    std::string createdAtIso8601;
    std::vector<std::string> sections;
    std::string payloadSha256;
    bool encrypted{true};
};

struct ServiceSession {
    std::string sessionId;
    std::string technicianId;
    std::uint64_t issuedAtEpochMs{0};
    std::uint64_t expiresAtEpochMs{0};
    bool diagnosticsAllowed{true};
    bool updateAllowed{false};
    bool configurationWriteAllowed{false};
};

struct CrashRecord {
    std::string recordId;
    std::string deviceId;
    std::string firmwareVersion;
    std::string resetReason;
    std::string panicSummary;
    std::string stackFingerprint;
    std::uint64_t timestampEpochMs{0};
};

} // namespace lynq::service
