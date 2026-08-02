export class RevANodeSimulator {
  constructor({ nodeId, name, clock = () => Date.now() }) {
    this.nodeId = nodeId;
    this.name = name;
    this.clock = clock;
    this.paired = false;
    this.online = false;
    this.uptimeSeconds = 0;
  }

  announce() {
    return {
      nodeId: this.nodeId,
      displayName: this.name,
      hardwareProfile: "rev-a-m5stack",
      firmwareVersion: "1.2.0",
      capabilities: ["wifi", "ble", "ir", "rf433", "ota"]
    };
  }

  pair(code) {
    if (typeof code !== "string" || code.length < 6) {
      throw new Error("invalid pairing code");
    }
    this.paired = true;
    this.online = true;
  }

  heartbeat() {
    if (!this.paired) throw new Error("node is not paired");
    this.uptimeSeconds += 30;
    return {
      nodeId: this.nodeId,
      observedAtEpochMs: this.clock(),
      uptimeSeconds: this.uptimeSeconds,
      wifiRssiDbm: -48,
      freeHeapBytes: 210000,
      rf433Ready: true,
      irReady: true
    };
  }
}
