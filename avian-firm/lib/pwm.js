pwmThrottle = 0;
pwmYaw = 50;
pwmPitch = 50;
pwmRoll = 50;

SerialPort = require("serialport").SerialPort
	serialPort = new SerialPort("/dev/ttyUSB0", {
  	baudrate: 9600
	});

exports.start = function start(client){
	
	console.log('a user connected');
	client.on('throttle',function(data){

		if (data == 'up' && pwmThrottle <100){
			pwmThrottle+=1;
			console.log(pwmThrottle);
			serialPort.write(String(pwmThrottle)+String(pwmRoll)+String(pwmPitch));
		}
		if (data == 'down' && pwmThrottle >0){
			pwmThrottle-=1;
			console.log(pwmThrottle);
			serialPort.write(String(pwmThrottle)+String(pwmRoll)+String(pwmPitch));
		}
		client.emit('valueThrottle',pwmThrottle);
		});

	client.on('yaw',function(data){

		if (data == 'up' && pwmYaw<100){
			pwmYaw+=1;
			console.log(pwmYaw);
			}
		if (data == 'down' && pwmYaw >0){
			pwmYaw-=1;
			console.log(pwmYaw);
		}
		client.emit('valueYaw',pwmYaw);
		});

	client.on('pitch',function(data){

		if (data == 'up' && pwmPitch<100){
			pwmPitch+=1;
			console.log(pwmPitch);
			serialPort.write(String(pwmThrottle)+String(pwmRoll)+String(pwmPitch));
		}
		if (data == 'down' && pwmPitch >0){
			pwmPitch-=1;
			console.log(pwmPitch);
			serialPort.write(String(pwmThrottle)+String(pwmRoll)+String(pwmPitch));
		}
	client.emit('valuePitch',pwmPitch);
	});

	client.on('roll',function(data){

		if (data == 'up' && pwmRoll<100){
			pwmRoll+=1;
			console.log(pwmRoll);
			serialPort.write(String(pwmThrottle)+String(pwmRoll)+String(pwmPitch));
		}
		if (data == 'down' && pwmRoll >0){
			pwmRoll-=1;
			console.log(pwmRoll);
			serialPort.write(String(pwmThrottle)+String(pwmRoll)+String(pwmPitch));
		}
	client.emit('valueRoll',pwmRoll);
	});
	
	client.on('oriax',function(data){
		ax=90-data*10;
		ax=Math.round(ax);
		//board.servoWrite(throttle, ax);
		console.log(ax);
	});
}
