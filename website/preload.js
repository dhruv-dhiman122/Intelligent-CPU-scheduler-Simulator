const { contextBridge, ipcRenderer } = require("electron");

contextBridge.exposeInMainWorld("api", {
    runScheduler: (data) => ipcRenderer.send("run-scheduler", data),

    onResult: (callback) =>
        ipcRenderer.on("scheduler-result", (event, result) => callback(result))
});
