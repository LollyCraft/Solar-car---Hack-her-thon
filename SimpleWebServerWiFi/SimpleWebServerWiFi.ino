/*
  WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 9.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the WiFi.begin() call accordingly.

 Circuit:
 * WiFi shield attached
 * LED attached to pin 9

 created 25 Nov 2012
 by Tom Igoe
 */
#include <SPI.h>
#include <WiFi101.h>

#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);      // initialize serial communication
  pinMode(9, OUTPUT);      // set the LED pin mode

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);       // don't continue
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWiFiStatus();                        // you're connected now, so print out the status
}


const String html = "<!DOCTYPE html>"\
"<html>"\
"<body>"\
"Test"\
"<img src=\"https://i.pinimg.com/originals/85/49/dd/8549ddae0806d4f4f10383f1031538c1.jpg\" alt=\"car\">"\
"</body>"\
"</html>";

//const String html_2 = "<!DOCTYPE html>"\
//"<html>"\
//"<body>"\
//"Test"\
//"<img src=\"https://i.pinimg.com/originals/c2/eb/5c/c2eb5c52c73fba8fc42cb2dc398dd562.jpg\" alt=\"car\">"\
//"</body>"\
//"</html>";

//serial connection to js from arduino to read the output variables

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
              client.println(html);
    
//            client.println("<!DOCTYPE html>");      //web page is made using html
//            client.println("<html>");
//            client.println("<head>");
//            client.println("<title>Solar Energy game (High Views)</title>");
//            client.print("Click <a href=\"/H\">here</a> turn the LED on pin 9 on<br>");
//            client.print("Click <a href=\"/L\">here</a> turn the LED on pin 9 off<br>");
//            client.print("hello there bye");
//            client.println("</head>");
//            client.println("<body>");
//            client.println("<h1>A Webserver Tutorial </h1>");
////            client.println("<img src=\"https://previews.dropbox.com/p/thumb/ABERXvBZaCV1Le16RoDg7g-8hRCkoHtosIYFUEVmyGPKy-5N1VUazwvQpx_XcU7nMkEZDFoULYRz4KRB_wuG8S1dtekiYUI1h0weXH1Cmaq7j6Bf_0BMfKNKBh2-bw5pqT8cqyuePJQCXlj5O0jXof5JER68EAgQ0wa8eU1Q8IzKH4_x6XcEzKCZ3MzGSxvCIUIXS2bf4Qo5kkijRN7nppkWT-xrWF9ooDttz2PebrTNolPzx9yVzCfaOW9L4XxkF9DKoD364gxgiZD_KY9zOX9nQeB7rUX84ZIEhN_BuaHC4TmLeOAC7f8b7Uzp3jfsYck31bRpJS0V4Oq4lnUPwW07sYH2H-QvohcPUQ6eEKFMrw/p.jpeg?fv_content=true&size_mode=5\" alt=\"car\">");
//            client.println("</body>");
//            client.println("</html>");
            
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(9, HIGH);
          Serial.println(HIGH);// GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(9, LOW);   
          Serial.println(LOW);// GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
