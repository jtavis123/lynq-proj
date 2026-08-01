import assert from 'node:assert/strict';
import test from 'node:test';

import { createHandler } from '../src/handler.js';

function directive(namespace, name, endpoint = true) {
  const value = {
    directive: {
      header: { namespace, name, payloadVersion: '3', messageId: 'msg-1', correlationToken: 'corr-1' },
      payload: {}
    }
  };
  if (endpoint) {
    value.directive.endpoint = {
      scope: { type: 'BearerToken', token: 'valid-token' },
      endpointId: 'endpoint-1',
      cookie: { hubId: 'hub-1', nodeId: 'node-1', commandId: 'cmd-1', deviceClass: 'light' }
    };
  } else {
    value.directive.payload.scope = { type: 'BearerToken', token: 'valid-token' };
  }
  return value;
}

const dependencies = {
  tokens: { validate: async (token) => ({ valid: token === 'valid-token', userId: 'user-1' }) },
  cloud: {
    listEndpoints: async () => [{ endpointId: 'endpoint-1', friendlyName: 'Pool Lights', hubId: 'hub-1', nodeId: 'node-1', commandId: 'cmd-1', supportsPower: true, displayCategories: ['LIGHT'] }],
    routeCommand: async () => ({ accepted: true })
  }
};

test('discovers LYNQ endpoints', async () => {
  const response = await createHandler(dependencies)(directive('Alexa.Discovery', 'Discover', false));
  assert.equal(response.event.header.name, 'Discover.Response');
  assert.equal(response.event.payload.endpoints[0].friendlyName, 'Pool Lights');
});

test('routes power commands to the LYNQ cloud', async () => {
  const response = await createHandler(dependencies)(directive('Alexa.PowerController', 'TurnOn'));
  assert.equal(response.event.header.name, 'Response');
  assert.equal(response.context.properties[0].value, 'ON');
});

test('rejects invalid tokens', async () => {
  const request = directive('Alexa.PowerController', 'TurnOn');
  request.directive.endpoint.scope.token = 'bad-token';
  const response = await createHandler(dependencies)(request);
  assert.equal(response.event.payload.type, 'INVALID_AUTHORIZATION_CREDENTIAL');
});

test('handles AcceptGrant', async () => {
  const response = await createHandler(dependencies)({ directive: { header: { namespace: 'Alexa.Authorization', name: 'AcceptGrant', payloadVersion: '3', messageId: 'grant-1' }, payload: { grant: { type: 'OAuth2.AuthorizationCode', code: 'code' }, grantee: { type: 'BearerToken', token: 'token' } } } });
  assert.equal(response.event.header.name, 'AcceptGrant.Response');
});
