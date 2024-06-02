"use strict";
var __defProp = Object.defineProperty;
var __getOwnPropDesc = Object.getOwnPropertyDescriptor;
var __getOwnPropNames = Object.getOwnPropertyNames;
var __hasOwnProp = Object.prototype.hasOwnProperty;
var __export = (target, all) => {
  for (var name in all)
    __defProp(target, name, { get: all[name], enumerable: true });
};
var __copyProps = (to, from, except, desc) => {
  if (from && typeof from === "object" || typeof from === "function") {
    for (let key of __getOwnPropNames(from))
      if (!__hasOwnProp.call(to, key) && key !== except)
        __defProp(to, key, { get: () => from[key], enumerable: !(desc = __getOwnPropDesc(from, key)) || desc.enumerable });
  }
  return to;
};
var __toCommonJS = (mod) => __copyProps(__defProp({}, "__esModule", { value: true }), mod);
var validate_hash_exports = {};
__export(validate_hash_exports, {
  default: () => handler,
  validateHash: () => validateHash
});
module.exports = __toCommonJS(validate_hash_exports);
var import_crypto = require("crypto");
async function handler(req, res) {
  if (req.method !== "POST") {
    return res.status(405).send(JSON.stringify({ error: "Method not allowed" }));
  }
  if (!req.body.initData) {
    return res.status(400).send(
      JSON.stringify({
        error: "Missing required field hash"
      })
    );
  }
  if (!process.env.BOT_TOKEN) {
    return res.status(500).send(JSON.stringify({ error: "Internal server error" }));
  }
  const data = { ...req.body.initData, user: JSON.stringify(req.body.initData.user) };
  const isValid = await isHashValid(data, process.env.BOT_TOKEN);
  if (isValid) {
    return res.status(200).send(JSON.stringify({ ok: true }));
  }
  return res.status(403).send(JSON.stringify({ error: "Invalid hash" }));
}
const validateHash = async (initData) => {
  if (!initData) {
    throw new Error("Missing required field hash");
  }
  if (!process.env.BOT_TOKEN) {
    throw new Error("Internal server error");
  }
  const data = {
    hash: initData.hash,
    auth_date: String(initData.auth_date),
    user: JSON.stringify(initData.user)
  };
  const isValid = await isHashValid(data, process.env.BOT_TOKEN);
  if (isValid) {
    return true;
  }
  throw new Error("Invalid hash");
};
async function isHashValid(data, botToken) {
  const encoder = new TextEncoder();
  const checkString = Object.keys(data).filter((key) => key !== "hash").map((key) => `${key}=${data[key]}`).sort().join("\n");
  const secretKey = await import_crypto.webcrypto.subtle.importKey(
    "raw",
    encoder.encode("WebAppData"),
    { name: "HMAC", hash: "SHA-256" },
    true,
    ["sign"]
  );
  const secret = await import_crypto.webcrypto.subtle.sign("HMAC", secretKey, encoder.encode(botToken));
  const signatureKey = await import_crypto.webcrypto.subtle.importKey(
    "raw",
    secret,
    { name: "HMAC", hash: "SHA-256" },
    true,
    ["sign"]
  );
  const signature = await import_crypto.webcrypto.subtle.sign("HMAC", signatureKey, encoder.encode(checkString));
  const hex = Buffer.from(signature).toString("hex");
  return data.hash === hex;
}
// Annotate the CommonJS export names for ESM import in node:
0 && (module.exports = {
  validateHash
});
