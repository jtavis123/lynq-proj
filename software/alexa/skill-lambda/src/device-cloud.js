export class DeviceCloud {
  constructor({ listEndpoints, routeCommand }) {
    if (typeof listEndpoints !== 'function' || typeof routeCommand !== 'function') {
      throw new TypeError('DeviceCloud requires listEndpoints and routeCommand functions');
    }
    this.listEndpointsFn = listEndpoints;
    this.routeCommandFn = routeCommand;
  }

  listEndpoints(userId) {
    return this.listEndpointsFn(userId);
  }

  routeCommand(command) {
    return this.routeCommandFn(command);
  }
}
