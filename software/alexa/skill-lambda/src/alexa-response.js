import crypto from 'node:crypto';

export function messageId() {
  return crypto.randomUUID();
}

export function baseHeader(namespace, name, correlationToken) {
  const header = {
    namespace,
    name,
    payloadVersion: '3',
    messageId: messageId()
  };
  if (correlationToken) header.correlationToken = correlationToken;
  return header;
}

export function discoveryResponse(endpoints) {
  return {
    event: {
      header: baseHeader('Alexa.Discovery', 'Discover.Response'),
      payload: { endpoints }
    }
  };
}

export function successResponse(directive, properties = []) {
  const endpoint = directive.endpoint;
  return {
    context: { properties },
    event: {
      header: baseHeader('Alexa', 'Response', directive.header.correlationToken),
      endpoint: {
        scope: endpoint.scope,
        endpointId: endpoint.endpointId
      },
      payload: {}
    }
  };
}

export function errorResponse(directive, type, message) {
  const event = {
    header: baseHeader('Alexa', 'ErrorResponse', directive.header.correlationToken),
    payload: { type, message }
  };
  if (directive.endpoint) {
    event.endpoint = {
      scope: directive.endpoint.scope,
      endpointId: directive.endpoint.endpointId
    };
  }
  return { event };
}

export function acceptGrantResponse() {
  return {
    event: {
      header: baseHeader('Alexa.Authorization', 'AcceptGrant.Response'),
      payload: {}
    }
  };
}
