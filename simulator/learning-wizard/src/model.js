export const initialState = { step: "device", deviceId: "", nodeId: "", transport: "ir", name: "", captured: false, tested: false, saved: false };
export function chooseDevice(s,id){ return {...s,deviceId:id,step:"node"}; }
export function chooseNode(s,id,transport){ return {...s,nodeId:id,transport,step:"capture"}; }
export function captureSignal(s){ if(!s.nodeId) throw new Error("node required"); return {...s,captured:true,step:"test"}; }
export function testReplay(s){ if(!s.captured) throw new Error("capture required"); return {...s,tested:true,step:"name"}; }
export function saveCommand(s,name){ const n=name.trim(); if(n.length<2) throw new Error("name too short"); return {...s,name:n,saved:true,step:"complete"}; }
