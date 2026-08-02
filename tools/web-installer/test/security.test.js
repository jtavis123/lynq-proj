import test from "node:test";
import assert from "node:assert/strict";
import {
  createOneTimeToken,
  hashToken,
  verifyToken,
  redactObject
} from "../src/security.js";

test("creates and verifies setup token", () => {
  const token = createOneTimeToken();
  const salt = "salt";
  const hash = hashToken(token, salt);
  assert.equal(verifyToken(token, salt, hash), true);
  assert.equal(verifyToken("wrong", salt, hash), false);
});

test("redacts secrets from logs", () => {
  const value = redactObject({
    username:"tech",
    password:"hidden",
    accessToken:"hidden"
  });
  assert.equal(value.username, "tech");
  assert.equal(value.password, "[REDACTED]");
  assert.equal(value.accessToken, "[REDACTED]");
});
