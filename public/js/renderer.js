const ipcRenderer = require('electron').ipcRenderer;
const hours = document.querySelector('#hours');
const minutes = document.querySelector('#minutes');
const seconds = document.querySelector('#seconds');
const update = document.querySelector('#update');

update.onclick = () => {
	const parsedHours = parseInt(hours.value, 10);
	const parsedMinutes = parseInt(minutes.value, 10);
	const parsedSeconds = parseInt(seconds.value, 10);
	if (!isNaN(parsedHours) && !isNaN(parsedMinutes) && !isNaN(parsedSeconds)) {
		const newTime = parsedHours * 3600 + parsedMinutes * 60 + parsedSeconds;
		ipcRenderer.send('newHour', newTime);
	}
};
