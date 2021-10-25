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

String TEXT = "no \n data";
void setup() {
  Serial.begin(115200);

  TEXT.replace("\n","\\n");
  //Serial.println(TEXT);

  // Create SoftAP
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);


  //Serial.print("Connect to My access point: ");
  //Serial.println(ssid);

  server.on("/", handle_root);
 server.on("/table", handle_table);

  server.begin();
  //Serial.println("HTTP server started");
  delay(100);
}

void loop() {
  server.handleClient();
  if (Serial.available() > 0){
        TEXT = Serial.readString();
    /*while (Serial.available() > 0){
      TEXT += Serial.readString();
    }*/
    TEXT.replace("\n","\\n");
    //Serial.println("New Text: " + TEXT + ";");
  }
}

// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>  <html>   <head>    <meta charset='utf-8'>    <title>Name Input</title>   </head>   <body>    <form action='/'>     New Player:     <br>     <input type='test' name='name'>     <input type='submit' name='submit'>    </form>    <iframe src='/table'></iframe>   </body>  </html>";
String TABLE_1 = "<!DOCTYPE html>  <html>   <head>    <meta charset='utf-8'>    <title>Top-table</title>    <META HTTP-EQUIV='refresh' CONTENT='5'>   </head>   <body>    <p id='Top'>test</p>    <script type='text/javascript'>     var list = '";
String TABLE_2 = "';     document.getElementById('Top').innerHTML = list;    </script>   </body>  </html>";
// Handle root url (/)
void handle_root() {
  //Serial.println("got name: " + server.arg("name") + ";");
  Serial.println(server.arg("name"));
  server.send(200, "text/html", HTML);
}
void handle_table() {
    //Serial.println("send Text: " + TEXT + ";");
  server.send(200, "text/html", String(TABLE_1) + String(TEXT) + String(TABLE_2));
}
