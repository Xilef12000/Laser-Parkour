#include <WiFi.h>
#include <WebServer.h>
#include <SPI.h>
#include <SD.h>

// SSID & Password
const char* ssid = "LaserParkour";  // Enter your SSID here
const char* password = "testpassword";  //Enter your Password here (it must be et leased  eight characters long)

// IP Address details
IPAddress local_ip(192, 168, 1, 1); //192.168.1.1
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)
File myFile;

String HTML = "";
String TABLE_1 = "";
String TABLE_2 = "";
String TEXT = "no Top-list";
void setup() {
  Serial.begin(9600);
  if (!SD.begin(5)) {
    while (1);
  }
  myFile = SD.open("/name.htm", FILE_READ);
  while (myFile.available()) {
    HTML += (char)myFile.read();
  }
  myFile.close();
  myFile = SD.open("/table1.htm", FILE_READ);
  while (myFile.available()) {
    TABLE_1 += (char)myFile.read();
  }
  myFile.close();
  myFile = SD.open("/table2.htm", FILE_READ);
  while (myFile.available()) {
    TABLE_2 += (char)myFile.read();
  }
  myFile.close();
  TEXT.trim();

  // Create SoftAP
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);


  //Serial.print("Connect to My access point: ");
  //Serial.println(ssid);

  server.on("/", handle_root);
  server.on("/table.htm", handle_table);

  server.begin();
  //Serial.println("HTTP server started");
  delay(100);
}

void loop() {
  server.handleClient();
  if (Serial.available() > 0) {
    TEXT = Serial.readString();
    /*while (Serial.available() > 0){
      TEXT += Serial.readString();
      }*/
    //TEXT.replace("\n","");
    TEXT.trim();
    //Serial.println("New Text: " + TEXT + ";");
  }
}


// Handle root url (/)
void handle_root() {
  //Serial.println("got name: " + server.arg("name") + ";");
  String NAME = server.arg("name");
  NAME.trim();
  Serial.print(NAME);
  server.send(200, "text/html", HTML);
}
void handle_table() {
  //Serial.println("send Text: " + TEXT + ";");
  server.send(200, "text/html", String(TABLE_1) + String(TEXT) + String(TABLE_2));
}
