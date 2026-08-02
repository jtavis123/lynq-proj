export class LynqCloudSimulator {
 constructor(){ this.hubs=new Map(); this.queue=[]; this.activity=[]; }
 registerHub(h){ if(!h.hubId||!h.householdId) throw new Error('invalid hub'); this.hubs.set(h.hubId,{...h}); }
 setOnline(id,online){ const h=this.hubs.get(id); if(!h) throw new Error('unknown hub'); this.hubs.set(id,{...h,online}); }
 enqueue(c){ const h=this.hubs.get(c.hubId); if(!h||h.householdId!==c.householdId) throw new Error('unauthorized'); this.queue.push({...c}); }
 next(id,now){ const h=this.hubs.get(id); if(!h?.online) return null; this.queue=this.queue.filter(c=>!(c.expiresAtEpochMs&&c.expiresAtEpochMs<=now)); const i=this.queue.findIndex(c=>c.hubId===id); if(i<0) return null; return this.queue.splice(i,1)[0]; }
 record(a){ this.activity.push({...a}); }
}
export function translateAlexa(d,devices,now){ const device=devices.find(x=>x.deviceId===d.endpointId&&x.enabled!==false); if(!device) throw new Error('endpoint unavailable'); const commandName=d.directiveName==='TurnOn'?'Power On':d.directiveName==='TurnOff'?'Power Off':d.directiveName; if(!device.commands.some(c=>c.enabled!==false&&c.commandName===commandName)) throw new Error('unsupported'); return {commandId:`alexa-${d.messageId}`,householdId:d.householdId,hubId:d.hubId,deviceId:d.endpointId,commandName,createdAtEpochMs:now,expiresAtEpochMs:d.expiresAtEpochMs}; }
