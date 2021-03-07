// Require the serialport node module
var SerialPort = require('serialport');
const Readline = SerialPort.parsers.Readline;

// Open the port
var port = new SerialPort("COM4", {
    baudRate: 9600,
});

var parser = port.pipe(new Readline({ delimiter: '\n' }));
parser.on('data', console.log);

var text = "------";
parser.on('data', printText);

function printText(data){
    text = '<br> </br>' + data;

    // console.log(text);
}



// we've started you off with Express (https://expressjs.com/)
// but feel free to use whatever libraries or frameworks you'd like through `package.json`.
const express = require("express");
const app = express();

// make all the files in 'public' available
// https://expressjs.com/en/starter/static-files.html
app.use(express.static("public"));

// https://expressjs.com/en/starter/basic-routing.html
app.get("/", (request, response) => {
  response.sendFile(__dirname + "/main.html");
});

// send the default array of dreams to the webpage
app.get("/arduinoResponse", (request, response) => {
  // express helps us take JS objects and send them as JSON
  response.json(text);
});

// listen for requests :)
const listener = app.listen(3000, () => {
  console.log("Your app is listening on port " + listener.address().port);
});
