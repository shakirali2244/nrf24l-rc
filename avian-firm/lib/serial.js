module.exports.SerialPort = require("serialport").SerialPort;
module.exports.serialPort = new module.exports.SerialPort("/dev/ttyUSB0", {
  	baudrate: 9600
	});