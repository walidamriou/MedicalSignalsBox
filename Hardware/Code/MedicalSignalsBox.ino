/*
Medical Signals Box project
Developed by Walid Amriou
2019 
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

/*  */
const char* ssid     = "MedicalSignalsBox";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "123456789msb";     // The password of the Wi-Fi network

String Html_page;  


ESP8266WebServer server(80);


void setup() {

wifiacesspoint(ssid,password,Html_page);

}

void loop() {
  server.handleClient();
  Html_page="<h1>You are connected ok?</h1>";  
  server.send(200, "text/html", Html_page);
}

void handleRoot() {
     server.send(200, "text/html", "empty");
}

void wifiacesspoint(const char *wifi_access_point_ssid,const char *wifi_access_point_password,String html_page_web){
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  
  IPAddress Ip(192, 168, 1, 22); //IP address where found the data
  IPAddress NMask(255, 255, 255, 0); //just mask address
  WiFi.softAPConfig(Ip, Ip, NMask);
  
  WiFi.softAP(wifi_access_point_ssid, wifi_access_point_password);
  
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}
