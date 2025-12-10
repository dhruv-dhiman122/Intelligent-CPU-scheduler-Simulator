// server.js
const express = require("express");
const cors = require("cors");
const { execFile } = require("child_process");
const path = require("path");

const app = express();
app.use(cors());
app.use(express.json({ limit: "5mb" }));

app.get("/", (req, res) => res.json({ ok: true }));

app.post("/run", (req, res) => {
  try {
    const { algo, processData, quantum, priorityOrder } = req.body || {};
    if (!algo || !processData) return res.status(400).json({ error: "algo or processData missing" });

    const exe = process.platform === "win32" ? "scheduling.exe" : "./scheduling";
    const exePath = path.join(__dirname, exe);
    const args = [algo, processData.toString(), (quantum || '2').toString(), (priorityOrder || 'high').toString()];

    console.log("Running:", exePath, args);

    execFile(exePath, args, { timeout: 20000, maxBuffer: 1024 * 1024 }, (err, stdout, stderr) => {
      if (err) {
        console.error("Execution error:", err, stderr);
        return res.status(500).json({ error: "Execution failed", details: stderr || err.message });
      }
      if (!stdout) return res.status(500).json({ error: "C++ returned empty output" });
      try {
        const parsed = JSON.parse(stdout);
        return res.json(parsed);
      } catch (e) {
        console.error("Parse error:", e, "raw:", stdout);
        return res.status(500).json({ error: "Invalid JSON from C++", raw: stdout });
      }
    });

  } catch (e) {
    console.error("Server error:", e);
    return res.status(500).json({ error: e.message });
  }
});

const PORT = 3000;
app.listen(PORT, () => console.log(`🔥 Backend listening at http://localhost:${PORT}`));
