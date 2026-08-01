export class DeliveryService {
  constructor({ queue, sessions }) {
    this.queue = queue;
    this.sessions = sessions;
  }

  async submit(command) {
    const queued = this.queue.enqueue(command);
    await this.flushHub(queued.hubId);
    return this.queue.get(queued.commandId);
  }

  async flushHub(hubId) {
    const session = this.sessions.getOnline(hubId);
    if (!session) return { delivered: 0, online: false };

    let delivered = 0;
    while (true) {
      const command = this.queue.nextForHub(hubId);
      if (!command) break;
      await session.send({
        type: "command",
        protocolVersion: 1,
        payload: command
      });
      delivered += 1;
    }
    return { delivered, online: true };
  }

  acknowledge(ack) {
    return this.queue.acknowledge(ack);
  }
}
