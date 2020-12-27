#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "index.h"

#include<SoftwareSerial.h>
SoftwareSerial s(D2,D3);
 
//SSID and Password to your ESP Access Point
const char* ssid = "ESPWebServer";
const char* password = "12345678";
 
ESP8266WebServer server(80); //Server on port 80
 
void handleRoot() {
  String str=MAIN_page;
  server.send(200, "text/html", str);
}

void handleLED() {
 String ledState = "OFF";
 String t_state = server.arg("LEDstate"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
 Serial.println(t_state);
 if(t_state == "1")
 {
  s.print("ON");
  ledState = "ON"; //Feedback parameter
 }
 else
 {
  s.print("OFF");
  ledState = "OFF"; //Feedback parameter  
 }
 
 server.send(200, "text/plane", ledState); //Send web page
}
 
//===============================================================
//                  SETUP
//===============================================================
void setup(void){
  Serial.begin(9600);
  Serial.println("");
  s.begin(9600);
  WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAP(ssid, password); 
  IPAddress myIP = WiFi.softAPIP(); //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(myIP);
 
  server.on("/", handleRoot);
  server.on("/setLED", handleLED);
  
  server.begin();                  
  Serial.println("HTTP server started");
  s.write(5);
}

void loop()
{
  server.handleClient();
}
