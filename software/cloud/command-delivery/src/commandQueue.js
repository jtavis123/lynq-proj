import crypto from "node:crypto";

export class CommandQueue {
  constructor({ clock = () => Date.now(), ttlMs = 30_000 } = {}) {
    this.clock = clock;
    this.ttlMs = ttlMs;
    this.pending = new Map();
    this.completed = new Map();
  }

  enqueue(command) {
    if (!command?.hubId || !command?.endpointId || !command?.action) {
      throw new TypeError("hubId, endpointId and action are required");
    }

    const commandId = command.commandId ?? crypto.randomUUID();
    const existing = this.pending.get(commandId) ?? this.completed.get(commandId);
    if (existing) return existing;

    const now = this.clock();
    const record = {
      commandId,
      hubId: command.hubId,
      endpointId: command.endpointId,
      action: command.action,
      parameters: command.parameters ?? {},
      correlationId: command.correlationId ?? commandId,
      createdAtMs: now,
      expiresAtMs: now + this.ttlMs,
      attempt: 0,
      state: "queued"
    };

    this.pending.set(commandId, record);
    return record;
  }

  nextForHub(hubId) {
    const now = this.clock();
    for (const record of this.pending.values()) {
      if (record.hubId !== hubId) continue;
      if (record.state !== "queued") continue;
      if (record.expiresAtMs <= now) {
        record.state = "expired";
        this.pending.delete(record.commandId);
        this.completed.set(record.commandId, record);
        continue;
      }
      record.state = "delivering";
      record.attempt += 1;
      return structuredClone(record);
    }
    return null;
  }

  acknowledge({ commandId, status, detail = "" }) {
    const record = this.pending.get(commandId);
    if (!record) {
      return this.completed.get(commandId) ?? null;
    }

    record.state = status === "success" ? "completed" : "failed";
    record.detail = detail;
    record.completedAtMs = this.clock();
    this.pending.delete(commandId);
    this.completed.set(commandId, record);
    return structuredClone(record);
  }

  get(commandId) {
    const record = this.pending.get(commandId) ?? this.completed.get(commandId);
    return record ? structuredClone(record) : null;
  }
}
