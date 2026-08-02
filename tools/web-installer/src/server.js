import http from "node:http";
import crypto from "node:crypto";
import {
  createOneTimeToken,
  hashToken,
  verifyToken,
  redactObject
} from "./security.js";

const bindAddress = process.env.LYNQ_BIND ?? "127.0.0.1";
const port = Number(process.env.LYNQ_PORT ?? 8787);
const setupToken = process.env.LYNQ_SETUP_TOKEN ?? createOneTimeToken();
const salt = crypto.randomBytes(16).toString("hex");
const expectedHash = hashToken(setupToken, salt);
let consumed = false;

const html = `<!doctype html>
<html><head><meta charset="utf-8"><meta name="viewport" content="width=device-width">
<title>LYNQ Installer</title>
<style>
body{font-family:system-ui;margin:0;background:#0f1115;color:#fff}
main{max-width:720px;margin:50px auto;padding:28px;background:#1b1f26;border-radius:20px}
input,button{font:inherit;padding:12px;border-radius:10px;border:0}
input{width:100%;margin:8px 0 16px}
button{background:#297ec0;color:#fff;cursor:pointer}
small{color:#aab2bf}
</style></head>
<body><main><h1>LYNQ Secure Installer</h1>
<p>Enter the one-time setup token displayed in the terminal.</p>
<input id="token" type="password" autocomplete="one-time-code">
<button id="login">Open Installer</button>
<pre id="result"></pre>
<small>Local computer access only. Token expires after successful use.</small>
<script>
login.onclick=async()=>{
 const r=await fetch("/api/session",{method:"POST",
 headers:{"content-type":"application/json"},
 body:JSON.stringify({token:token.value})});
 result.textContent=JSON.stringify(await r.json(),null,2);
};
</script></main></body></html>`;

const server = http.createServer(async (req, res) => {
  res.setHeader("content-security-policy",
    "default-src 'self'; style-src 'unsafe-inline'; script-src 'unsafe-inline'");
  res.setHeader("x-content-type-options", "nosniff");
  res.setHeader("cache-control", "no-store");

  if (req.method === "GET" && req.url === "/") {
    res.writeHead(200, {"content-type":"text/html; charset=utf-8"});
    res.end(html);
    return;
  }

  if (req.method === "POST" && req.url === "/api/session") {
    let body = "";
    for await (const chunk of req) body += chunk;
    const request = JSON.parse(body || "{}");

    if (consumed ||
        typeof request.token !== "string" ||
        !verifyToken(request.token, salt, expectedHash)) {
      res.writeHead(401, {"content-type":"application/json"});
      res.end(JSON.stringify({ok:false,error:"Unauthorized"}));
      return;
    }

    consumed = true;
    const sessionId = crypto.randomUUID();
    res.writeHead(200, {"content-type":"application/json"});
    res.end(JSON.stringify({
      ok:true,
      sessionId,
      availableSteps:[
        "Detect Hub",
        "Backup factory firmware",
        "Install Hub image",
        "Enroll Nodes",
        "Restore configuration"
      ]
    }));
    console.log("Authenticated installer session:",
      redactObject({sessionId, setupToken}));
    return;
  }

  res.writeHead(404);
  res.end();
});

server.listen(port, bindAddress, () => {
  console.log(`LYNQ installer: http://${bindAddress}:${port}`);
  console.log(`One-time setup token: ${setupToken}`);
});
