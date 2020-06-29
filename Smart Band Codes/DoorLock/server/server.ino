#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include<Servo.h>              //Servo library
 
Servo servo_test;        //initialize a servo object for the connected servo  
                
int angle = 0;    

const char* ssid = "ESP_D54736";  // SSID of NODEMCU
//const char* password = "123";   //

ESP8266WebServer server(80);    //Specify port for TCP connection

void handleRoot() {
        for(angle = 0; angle < 180; angle += 1)    // command to move from 0 degrees to 180 degrees 
  {                                  
    servo_test.write(90);                 //command to rotate the servo to the specified angle
    delay(15);                       
  } 
 
  delay(1000);
  
  for(angle = 180; angle>=1; angle-=5)     // command to move from 180 degrees to 0 degrees 
  {                                
    servo_test.write(180);              //command to rotate the servo to the specified angle
    delay(5);                       
  } 

    delay(1000);
        String s = "\r\n\r\n<!DOCTYPE HTML>\r\n<html><h1>Esp8266 Communication</h1> ";
        s += "<p>Success!!!</html>\r\n\r\n";
        server.send(200,"text/html",s);      //Reply to the client
}


void setup() {
  delay(200);                           //Stable Wifi
  Serial.begin(115200);                 //Set Baud Rate
  pinMode(16, OUTPUT);                   //Led/Solenoid at pin 2
  WiFi.softAP(ssid);//, password);      //In Access Point Mode

  IPAddress myIP = WiFi.softAPIP();     //Check the IP assigned. Put this Ip in the client host.
  Serial.print("AP IP address: ");
  Serial.println(myIP);                 //Print the esp8266-01 IP(Client must also be on the save IP series)
  server.on("/Led", handleRoot);           //Checking client connection
  server.begin();                       // Start the server
  Serial.println("Server started");
  servo_test.attach(16);      // attach the signal pin of servo to pin9 of arduino
}

void loop() {
  // Check if a client has connected. On first connection switch on the Solenoid on next switch off.
  server.handleClient();
}
