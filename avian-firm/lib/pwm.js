pwmThrottle = 0;
pwmYaw = 50;
pwmPitch = 50;
pwmRoll = 50;

ser = require('./serial');

exports.start = function start(client){
	
	console.log('a user connected');
	client.on('throttle',function(data){
		ser.serialPort.open(function (error) {
			  if ( error ) {
			    console.log('failed to open: '+error);
			  } else {
			    console.log('open');
			    ser.serialPort.on('data', function(data) {
			      console.log('data received: ' + data);
			    });
			    ser.serialPort.write(data, function(err, results) {
			      console.log('err ' + err);
			      console.log('results ' + results);
			    });
			  }
			});
		});
	/*
	client.on('yaw',function(data){
		if (data == 'up' && pwmYaw<99){
			pwmYaw+=1;
			console.log(pwmYaw);
			ser.serialPort.write(preparePayload(pwmThrottle,pwmRoll,pwmPitch,pwmYaw));
			}
		if (data == 'down' && pwmYaw >0){
			pwmYaw-=1;
			console.log(pwmYaw);
			ser.serialPort.write(preparePayload(pwmThrottle,pwmRoll,pwmPitch,pwmYaw));
		}
		client.emit('valueYaw',pwmYaw);
		});

	client.on('pitch',function(data){
		if (data == 'up' && pwmPitch<99){
			pwmPitch+=1;
			console.log(pwmPitch);
			ser.serialPort.write(preparePayload(pwmThrottle,pwmRoll,pwmPitch,pwmYaw));
		}
		if (data == 'down' && pwmPitch >0){
			pwmPitch-=1;
			console.log(pwmPitch);
			ser.serialPort.write(preparePayload(pwmThrottle,pwmRoll,pwmPitch,pwmYaw));
		}
	client.emit('valuePitch',pwmPitch);
	});

	client.on('roll',function(data){
		if (data == 'up' && pwmRoll<99){
			pwmRoll+=1;
			console.log(pwmRoll);
			ser.serialPort.write(preparePayload(pwmThrottle,pwmRoll,pwmPitch,pwmYaw));
		}
		if (data == 'down' && pwmRoll >0){
			pwmRoll-=1;
			console.log(pwmRoll);
			ser.serialPort.write(preparePayload(pwmThrottle,pwmRoll,pwmPitch,pwmYaw));
		}
	client.emit('valueRoll',pwmRoll);

	});
	
	client.on('oriax',function(data){
		ax=90-data*10;
		ax=Math.round(ax);
		//board.servoWrite(throttle, ax);
		console.log(ax);
	});


	function preparePayload(th,rl,pt,yw){ //optimize this SHIT
		if(th <10){
			var ths = "0" + th;
		}else{
			var ths =th;
		}
		if(rl <10){
			var rls = "0" + rl;
		}else{
			var rls =rl;
		}
		if(pt <10){
			var pts = "0" + pt;
		}else{
			var pts =pt;
		}
		if(yw <10){
			var yws = "0" + yw;
		}else{
			var yws =yw;
		}
		var payload = String(ths)+String(rls)+String(pts)+String(yws);
		console.log(payload);
		return payload

	}
	*/
}
