const { app, BrowserWindow, ipcMain } = require("electron");
const path = require("path");
const { execFile } = require("child_process");

function createWindow() {
    const win = new BrowserWindow({
        width: 1200,
        height: 800,
        webPreferences: {
            preload: path.join(__dirname, "preload.js"),
            contextIsolation: true,
            nodeIntegration: false,
            sandbox: false
        }
    });

    win.loadFile("index.html");
}

ipcMain.on("run-scheduler", (event, data) => {
    const exe = process.platform === "win32" ? "scheduling.exe" : "./scheduling";
    const exePath = path.join(__dirname, exe);

    execFile(
        exePath,
        [data.algo, data.processData, data.quantum, data.priorityOrder],
        (err, stdout) => {
            if (err) {
                event.sender.send("scheduler-result", { error: err.message });
                return;
            }

            try {
                const result = JSON.parse(stdout);
                event.sender.send("scheduler-result", result);
            } catch (e) {
                event.sender.send("scheduler-result", { error: "JSON parse error", raw: stdout });
            }
        }
    );
});

app.whenReady().then(createWindow);
