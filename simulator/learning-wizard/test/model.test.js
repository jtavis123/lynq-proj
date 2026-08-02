import test from "node:test";
import assert from "node:assert/strict";
import {initialState,chooseDevice,chooseNode,captureSignal,testReplay,saveCommand} from "../src/model.js";
test("completes learning workflow",()=>{ let s=chooseDevice(initialState,"tv"); s=chooseNode(s,"node-1","ir"); s=captureSignal(s); s=testReplay(s); s=saveCommand(s," Power "); assert.equal(s.step,"complete"); assert.equal(s.name,"Power"); });
test("rejects save before naming",()=>{ assert.throws(()=>saveCommand(initialState," ")); });
