#include "web.h"

const char* ssid = "Leave Kalina a Message!";

WebServer server(80);

// Pre-allocated memory for the input string (1024 + 1 for null terminator)
char inputString[1025] = { 0 };

int test_2[] = {1,2,3,4};

bool is_web_running = false;
unsigned long web_start_time = 0;
unsigned long web_stay_on_time = 600000;

// HTML web page with a text input field
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Message for Kalina</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <h2>Message for Kalina</h2>
  <form action="/get">
	<label for="inputString">Enter String (max 1024 chars):</label><br><br>
	<input type="text" id="inputString" name="inputString" maxlength="1024"><br><br>
	<input type="submit" value="Submit">
  </form>
  <h2>Current Message:</h2>
  <p>%input%</p>
</body>
</html>)rawliteral";

// The access points IP address and net mask
// It uses the default Google DNS IP address 8.8.8.8 to capture all 
// Android dns requests
IPAddress apIP(8, 8, 8, 8);
IPAddress netMsk(255, 255, 255, 0);

// DNS server 
const byte DNS_PORT = 53; 
DNSServer dnsServer;

// check if this string is an IP address
boolean isIp(String str) {
  for (size_t i = 0; i < str.length(); i++) {
	int c = str.charAt(i);
	if (c != '.' && (c < '0' || c > '9')) {
	  return false;
	}
  }
  return true;
}

String toStringIp(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) {
	res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}

// checks if the request is for the controllers IP, if not we redirect automatically to the
// captive portal 
boolean is_host_ip() {
  return isIp(server.hostHeader());
}

void redirect_to_host(){
	Serial.println("Request redirected to captive portal");
	server.sendHeader("Location", String("http://") + toStringIp(server.client().localIP()), true);
	server.send(302, "text/plain", "");   
	server.client().stop(); 
}


void handleRoot() {
	if (!is_host_ip()) { 
		redirect_to_host();
		return;
	}
	server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
	server.sendHeader("Pragma", "no-cache");
	server.sendHeader("Expires", "-1");

	String html = index_html;
	html.replace("%input%", String(inputString));
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

void handleNotFound() {
	if (!is_host_ip()) { 
		redirect_to_host();
		return;
	}
	// Serial.print("Not found, Redirecting");
	String message = F("File Not Found\n\n");
	message += F("URI: ");
	message += server.uri();
	message += F("\nMethod: ");
	message += (server.method() == HTTP_GET) ? "GET" : "POST";
	message += F("\nArguments: ");
	message += server.args();
	message += F("\n");

	for (uint8_t i = 0; i < server.args(); i++) {
		message += String(F(" ")) + server.argName(i) + F(": ") + server.arg(i) + F("\n");
	}
	server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
	server.sendHeader("Pragma", "no-cache");
	server.sendHeader("Expires", "-1");
	server.send(404, "text/plain", message);
}

void web_start() {
	Serial.println("Configuring access point...");
	WiFi.softAPConfig(apIP, apIP, netMsk);
	// its an open WLAN access point without a password parameter
	WiFi.softAP(ssid);
	Serial.print("AP IP address: ");
	Serial.println(WiFi.softAPIP());

	/* Setup the DNS server redirecting all the domains to the apIP */
	dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
	dnsServer.start(DNS_PORT, "*", apIP);

	/* Setup the web server */
	server.on("/", handleRoot);
	server.on("/generate_204", handleRoot);
	server.on("/redirect", handleRoot); // microsoft redirect
	server.on("/hotspot-detect.html",handleRoot); // apple call home
	server.on("/canonical.html", handleRoot);// firefox captive portal call home
	server.on("/success.txt", handleRoot);// firefox captive portal call home
	server.on("/ncsi.txt", handleRoot);
	server.on("/ncsi.txt", handleRoot);


	server.on("/get", handleInput);
	server.onNotFound(handleNotFound);
	server.begin(); // Web server start
	Serial.println("HTTP server started");

	is_web_running = true;
	web_start_time = millis();
}


void web_stop(){
	dnsServer.stop();
	server.close();
	WiFi.softAPdisconnect(true);
	Serial.println("Stopped Wifi-Server");
	is_web_running = false;
}


void web_run() {
	if (! is_web_running)
		return;
	if (millis() > web_start_time + web_stay_on_time)
		web_stop();

	
	// put your main code here, to run repeatedly:
	//DNS
	dnsServer.processNextRequest();
	//HTTP
	server.handleClient();
}

void web_disp() {
	scroll_disp_str(inputString, true);
}
