var express = require('express');
var fs = require('fs');
var app = express.createServer(express.logger());

var response_string = fs.readFileSync('index.html');
response_string = response_string.toString('utf-8');

app.get('/', function(request, response) {
  response.send(response_string);
  response.send("Hi!");
});

var port = process.env.PORT || 5000;
app.listen(port, function() {
  console.log("Listening on " + port);
});
