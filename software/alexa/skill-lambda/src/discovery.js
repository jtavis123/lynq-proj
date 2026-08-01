import { discoveryResponse } from './alexa-response.js';

function capabilitiesFor(device) {
  const capabilities = [
    { type: 'AlexaInterface', interface: 'Alexa', version: '3' },
    {
      type: 'AlexaInterface',
      interface: 'Alexa.EndpointHealth',
      version: '3',
      properties: { supported: [{ name: 'connectivity' }], proactivelyReported: true, retrievable: true }
    }
  ];

  if (device.supportsPower) {
    capabilities.push({
      type: 'AlexaInterface',
      interface: 'Alexa.PowerController',
      version: '3',
      properties: { supported: [{ name: 'powerState' }], proactivelyReported: true, retrievable: true }
    });
  }

  if (device.supportsScene) {
    capabilities.push({
      type: 'AlexaInterface',
      interface: 'Alexa.SceneController',
      version: '3',
      supportsDeactivation: Boolean(device.supportsSceneDeactivation),
      proactivelyReported: true
    });
  }

  return capabilities;
}

export async function handleDiscovery({ userId, cloud }) {
  const devices = await cloud.listEndpoints(userId);
  const endpoints = devices.map((device) => ({
    endpointId: device.endpointId,
    manufacturerName: 'LYNQ',
    description: device.description ?? 'LYNQ controlled device',
    friendlyName: device.friendlyName,
    displayCategories: device.displayCategories ?? ['OTHER'],
    cookie: {
      hubId: device.hubId,
      nodeId: device.nodeId,
      commandId: device.commandId,
      deviceClass: device.deviceClass ?? 'generic'
    },
    capabilities: capabilitiesFor(device)
  }));
  return discoveryResponse(endpoints);
}
