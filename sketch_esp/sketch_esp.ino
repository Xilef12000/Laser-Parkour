#include <WiFi.h>
#include <WebServer.h>

// SSID & Password
const char* ssid = "LaserParkour";  // Enter your SSID here
const char* password = "testpw";  //Enter your Password here

// IP Address details
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

void setup() {
  Serial.begin(115200);

  // Create SoftAP
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);


  Serial.print("Connect to My access point: ");
  Serial.println(ssid);

  server.on("/", handle_root);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}

void loop() {
  server.handleClient();
}

// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>  <html>   <head>    <meta charset='utf-8'>    <title>Name Input</title>   </head>   <body>    <form action='/'>     New Player:     <br>     <input type='test' name='name'>     <input type='submit' name='submit'>    </form>   </body>  </html>";

// Handle root url (/)
void handle_root() {
  Serial.println(server.arg("name"));
  server.send(200, "text/html", HTML);
}
