import crypto from 'node:crypto';
import { acceptGrantResponse, errorResponse } from './alexa-response.js';
import { handleControl } from './control.js';
import { handleDiscovery } from './discovery.js';
import { DeviceCloud } from './device-cloud.js';
import { TokenValidator } from './token-validator.js';

function createDependencies() {
  const apiBase = process.env.LYNQ_API_BASE_URL;
  if (!apiBase) throw new Error('LYNQ_API_BASE_URL is required');

  const request = async (path, options = {}) => {
    const response = await fetch(`${apiBase}${path}`, options);
    if (!response.ok) throw new Error(`LYNQ API request failed: ${response.status}`);
    return response.json();
  };

  return {
    tokens: new TokenValidator({
      introspect: (token) => request('/oauth/introspect', {
        method: 'POST',
        headers: { 'content-type': 'application/json' },
        body: JSON.stringify({ token })
      })
    }),
    cloud: new DeviceCloud({
      listEndpoints: (userId) => request(`/v1/alexa/endpoints?userId=${encodeURIComponent(userId)}`),
      routeCommand: (command) => request('/v1/commands', {
        method: 'POST',
        headers: { 'content-type': 'application/json' },
        body: JSON.stringify(command)
      })
    })
  };
}

export function createHandler(dependencies = createDependencies()) {
  return async function handler(request) {
    const directive = request?.directive;
    if (!directive?.header) {
      return { event: { header: { namespace: 'Alexa', name: 'ErrorResponse', payloadVersion: '3', messageId: crypto.randomUUID() }, payload: { type: 'INVALID_DIRECTIVE', message: 'Missing directive header.' } } };
    }

    const { namespace, name } = directive.header;
    if (namespace === 'Alexa.Authorization' && name === 'AcceptGrant') {
      // Production implementation exchanges grant code for Alexa Event Gateway tokens.
      return acceptGrantResponse();
    }

    const token = directive.endpoint?.scope?.token ?? directive.payload?.scope?.token;
    const identity = await dependencies.tokens.validate(token);
    if (!identity.valid) {
      return errorResponse(directive, 'INVALID_AUTHORIZATION_CREDENTIAL', 'Account authorization is invalid or expired.');
    }

    if (namespace === 'Alexa.Discovery' && name === 'Discover') {
      return handleDiscovery({ userId: identity.userId, cloud: dependencies.cloud });
    }

    return handleControl({ directive, userId: identity.userId, cloud: dependencies.cloud });
  };
}

export const handler = async (request) => createHandler()(request);
