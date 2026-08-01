import { errorResponse, successResponse } from './alexa-response.js';

function isoNow() {
  return new Date().toISOString();
}

function powerProperty(value) {
  return {
    namespace: 'Alexa.PowerController',
    name: 'powerState',
    value,
    timeOfSample: isoNow(),
    uncertaintyInMilliseconds: 500
  };
}

export async function handleControl({ directive, userId, cloud }) {
  const { namespace, name } = directive.header;
  const endpoint = directive.endpoint;
  const cookie = endpoint?.cookie ?? {};

  if (!endpoint?.endpointId || !cookie.hubId || !cookie.nodeId || !cookie.commandId) {
    return errorResponse(directive, 'INVALID_DIRECTIVE', 'Endpoint routing metadata is incomplete.');
  }

  let action;
  let requestedState;
  if (namespace === 'Alexa.PowerController' && name === 'TurnOn') {
    action = 'activate';
    requestedState = 'ON';
  } else if (namespace === 'Alexa.PowerController' && name === 'TurnOff') {
    action = 'deactivate';
    requestedState = 'OFF';
  } else if (namespace === 'Alexa.SceneController' && name === 'Activate') {
    action = 'activate';
  } else if (namespace === 'Alexa.SceneController' && name === 'Deactivate') {
    action = 'deactivate';
  } else {
    return errorResponse(directive, 'INVALID_DIRECTIVE', `Unsupported directive ${namespace}.${name}.`);
  }

  const result = await cloud.routeCommand({
    userId,
    endpointId: endpoint.endpointId,
    hubId: cookie.hubId,
    nodeId: cookie.nodeId,
    commandId: cookie.commandId,
    deviceClass: cookie.deviceClass,
    action,
    correlationToken: directive.header.correlationToken,
    messageId: directive.header.messageId
  });

  if (!result?.accepted) {
    return errorResponse(directive, result?.errorType ?? 'ENDPOINT_UNREACHABLE', result?.message ?? 'The LYNQ Hub did not accept the command.');
  }

  const properties = requestedState ? [powerProperty(requestedState)] : [];
  return successResponse(directive, properties);
}
