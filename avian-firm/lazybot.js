
var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);

socket = require('./lib/pwm');

app.get('/', function(req, res){
res.sendfile('/home/pi/nrf24l-rc/avian-firm/lazybot.html');
});

app.get('/css/badger.css', function(req, res){
res.sendfile('/home/pi/nrf24l-rc/avian-firm/css/badger.css');
});

app.get('/gyro.html', function(req, res){
res.sendfile('/home/pi/nrf24l-rc/avian-firm/gyro.html');
});

http.listen(3000,function(){
console.log('listening on *:3000');
});



io.on('connection', function(req){
	socket.start(req);
});

