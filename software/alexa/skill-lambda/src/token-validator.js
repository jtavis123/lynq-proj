export class TokenValidator {
  constructor({ introspect }) {
    if (typeof introspect !== 'function') {
      throw new TypeError('TokenValidator requires an introspect function');
    }
    this.introspect = introspect;
  }

  async validate(token) {
    if (!token || typeof token !== 'string') {
      return { valid: false, reason: 'missing_token' };
    }
    const result = await this.introspect(token);
    if (!result?.active || !result.userId) {
      return { valid: false, reason: 'invalid_token' };
    }
    return { valid: true, userId: result.userId, scopes: result.scopes ?? [] };
  }
}
