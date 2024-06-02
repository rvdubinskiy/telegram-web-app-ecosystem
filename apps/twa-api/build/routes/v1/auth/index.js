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
var auth_exports = {};
__export(auth_exports, {
  default: () => auth_default
});
module.exports = __toCommonJS(auth_exports);
const authRoutes = async (app) => {
  app.post("/", async function(req, res) {
    try {
      const { webAppData } = req.body;
      const userId = 432443;
      const accessToken = await res.accessSign({ userId, webAppData });
      const refreshToken = await res.refreshSign({ userId, webAppData });
      res.send({ accessToken, refreshToken });
    } catch (e) {
      req.log.error(e);
      return res.badRequest("Could not create user");
    }
  });
};
var auth_default = authRoutes;
