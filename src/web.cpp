#include "web.h"

const char* ssid = "Leave Kalina a Message!";
const char* password = "12345678";

WebServer server(80);

// Pre-allocated memory for the input string (1024 + 1 for null terminator)
char inputString[1025] = { 0 };

bool is_running = false;

// HTML web page with a text input field
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP32 Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <h2>ESP32 Input Form</h2>
  <form action="/get">
    <label for="inputString">Enter String (max 1024 chars):</label><br><br>
    <input type="text" id="inputString" name="inputString" maxlength="1024"><br><br>
    <input type="submit" value="Submit">
  </form>
  <h2>Your Message:</h2>
  <p>%input%</p>
</body>
</html>)rawliteral";

String processor(const String& var){
  if(var == "input"){
    return String(inputString);
  }
  return String();
}

void handleRoot() {
	String html = index_html;
	html.replace("%input%", processor("input"));
	server.send(200, "text/html", html);
}

void handleInput() {
	if (server.hasArg("inputString")) {
		String input = server.arg("inputString");
		input.toCharArray(inputString, 1025); // Copy string to pre-allocated buffer
	}
	server.sendHeader("Location", "/");
	server.send(303);
	Serial.println(inputString);
}

void web_start() {
	WiFi.softAP(ssid, password);
	IPAddress IP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(IP);
	
	server.on("/", handleRoot);
	server.on("/get", handleInput);
	server.begin();
}

void web_stop() {
	server.close();
	WiFi.softAPdisconnect(true);
	Serial.print("Stopped Wifi-Server");
}

void web_run() {
	server.handleClient();
}

void web_disp() {
	scroll_disp_str(inputString, true);
}