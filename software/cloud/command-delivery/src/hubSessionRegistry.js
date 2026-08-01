export class HubSessionRegistry {
  constructor({ clock = () => Date.now(), staleAfterMs = 45_000 } = {}) {
    this.clock = clock;
    this.staleAfterMs = staleAfterMs;
    this.sessions = new Map();
  }

  connect({ hubId, sessionId, send }) {
    if (!hubId || !sessionId || typeof send !== "function") {
      throw new TypeError("hubId, sessionId and send are required");
    }

    const session = {
      hubId,
      sessionId,
      send,
      connectedAtMs: this.clock(),
      lastSeenAtMs: this.clock()
    };
    this.sessions.set(hubId, session);
    return session;
  }

  heartbeat(hubId) {
    const session = this.sessions.get(hubId);
    if (!session) return false;
    session.lastSeenAtMs = this.clock();
    return true;
  }

  disconnect(hubId, sessionId) {
    const session = this.sessions.get(hubId);
    if (!session || session.sessionId !== sessionId) return false;
    this.sessions.delete(hubId);
    return true;
  }

  getOnline(hubId) {
    const session = this.sessions.get(hubId);
    if (!session) return null;
    if (this.clock() - session.lastSeenAtMs > this.staleAfterMs) {
      this.sessions.delete(hubId);
      return null;
    }
    return session;
  }
}
