var express = require('express')
var http = require('http')
var net = require('net');

// Initialization of the express app
var app = express();
app.use(express.static(__dirname + '/'));

// Initialization of the HTTP server
var httpServer = http.createServer(app);
const port = 3000;

// Default HTML page
app.get('/', function (req, res) {
    res.send('index.html');
});

// Endpoint to obtain the data from the stream
app.get('/stream', function (req, res) {

    res.writeHead(200, {
        'Content-Type': 'video/x-msvideo',
    });

    var tcpServer = net.createServer(function (socket) {
        socket.on('data', function (data) {
            res.write(data);
        });
        socket.on('close', function (error) {
            console.log('Socket closed.');
            res.end();
        });
    });

    tcpServer.maxConnections = 1;

    tcpServer.listen(function () {
		// Connection with GStreamer
    });
});

// Endpoint to get information about the bitrate of the audio
app.post('/bitrate-info/audio', function (req, res) {
	// TODO Signal GStreamer and get information
});

// Endpoint to get information about the bitrate of the audio
app.post('/bitrate-info/video', function (req, res) {
	// TODO Signal GStreamer and get information
});

// Endpoint to stop the video and audio connection
app.post('/stop', function (req, res) {
	// TODO Signal GStreamer and stop connection
});

// Server starts listening for requests
httpServer.listen(port);
console.log(`Server listening at http://localhost:${port}`);

// Exception handling
process.on('uncaughtException', function (err) {
    console.log(err);
});
