/*
 * HTTP Client POST Request
 * Copyright (c) 2018, circuits4you.com
 * All rights reserved.
 * https://circuits4you.com 
 * Connects to WiFi HotSpot. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

/* Set these to your desired credentials. */
const char *ssid = "rajeshsms";  //ENTER YOUR WIFI SETTINGS
const char *password = "rajeshrj";

//Web/Server address to read/write from 
const char *host = "192.168.43.217";   //https://circuits4you.com website or IP address of server

//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  HTTPClient http;    //Declare object of class HTTPClient

  String ON, OFF, postData;
  OFF = "OFF";
  ON = "on"; 
  digitalWrite(LED_BUILTIN, LOW);
  delay(5000);
    //Read Analog value of LDR
  ON = "on";   //String to interger conversion
  Serial.println(ON);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000); 
  Serial.println(OFF);
  
  

  //Post Data
  postData = "status=" + ON + "&station=" + OFF ;
  
  http.begin("http://192.168.43.217/postdemo.php");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header

  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload

  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.end();  //Close connection
  
  //delay(5000);  //Post Data at every 5 seconds
}
//=======================================================================