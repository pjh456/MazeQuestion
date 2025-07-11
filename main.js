// main.js
const { app, BrowserWindow, ipcMain } = require('electron');
const { Worker } = require('worker_threads');
const path = require('path');

let win = null;
let vmWorker = null;

app.whenReady().then(() => {
    win = new BrowserWindow({
        width: 1000,
        height: 800,
        webPreferences: {
            preload: path.join(__dirname, 'preload.js'),
            contextIsolation: true,
            nodeIntegration: true
        }
    })

    win.loadFile('maze_viewer/menu.html');

    // win.webContents.openDevTools();
});

ipcMain.on('run-user-code', (event, code) => {
    if (vmWorker) { vmWorker.terminate(); }
    const workerPath = path.join(__dirname, 'maze_viewer', 'worker.js');
    vmWorker = new Worker(workerPath);

    vmWorker.on('message', (msg) => win.webContents.send('from-vm', msg));
    vmWorker.on('message', (msg) => win.webContents.send('from-system', msg));

    vmWorker.postMessage({ code });
});

ipcMain.on('get-data', (event, value) => {
    if (!vmWorker) return;

    vmWorker.postMessage({ id: value.id, data: value.data });
});
