import crypto from "node:crypto";

export function createOneTimeToken() {
  return crypto.randomBytes(18).toString("base64url");
}

export function hashToken(token, salt) {
  return crypto.scryptSync(token, salt, 32).toString("hex");
}

export function verifyToken(token, salt, expected) {
  const actual = Buffer.from(hashToken(token, salt), "hex");
  const target = Buffer.from(expected, "hex");
  return actual.length === target.length &&
    crypto.timingSafeEqual(actual, target);
}

export function redactObject(value) {
  const blocked = /password|token|secret|credential|privateKey/i;
  return Object.fromEntries(
    Object.entries(value).map(([key, item]) => [
      key,
      blocked.test(key) ? "[REDACTED]" : item
    ])
  );
}
