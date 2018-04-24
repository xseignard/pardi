const electron = require('electron');
const app = electron.app;
const BrowserWindow = electron.BrowserWindow;
const ipcMain = require('electron').ipcMain;

const path = require('path');
const url = require('url');

const serialport = require('serialport');
serialport.list((err, ports) => console.log('ports', ports));

// TODO: handle data sending to the clock

let mainWindow;

const createWindow = () => {
	mainWindow = new BrowserWindow({ width: 800, height: 250 });
	mainWindow.loadURL(
		url.format({
			pathname: path.join(__dirname, 'public', 'index.html'),
			protocol: 'file:',
			slashes: true,
		})
	);
	// mainWindow.webContents.openDevTools();
	mainWindow.on('closed', () => {
		mainWindow = null;
	});
};

app.on('ready', createWindow);
app.on('window-all-closed', () => {
	if (process.platform !== 'darwin') app.quit();
});

app.on('activate', () => {
	if (mainWindow === null) createWindow();
});

ipcMain.on('newHour', (event, arg) => {
	console.log(`New Hours: ${arg}`);
	// TODO: update hours
});
