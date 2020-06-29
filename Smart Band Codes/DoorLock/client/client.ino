#include <ESP8266WiFi.h>
#include <WiFiClient.h> 

const char* host = "192.168.4.1"; //Ip of the Host(Our Case NODEMCU as server. Its the ip of the NODEMCU as Access point)

void setup() {
  Serial.begin(115200);          //Baud Rate for Communication
  delay(10);                     //Baud rate prper initialization
  pinMode(2,INPUT);             
  WiFi.mode(WIFI_STA);          // esp8266 in station mode
  WiFi.begin("ESP_D54736");      //Connect to this SSID. In our case NODEMCU SSID.  

  while (WiFi.status() != WL_CONNECTED) {      //Wait for getting IP assigned by Access Point/ DHCP. 
                                               //Our case  NODEMCU as Access point will assign IP to esp8266.
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());            
}

void loop() {

         if(digitalRead(2)==1)//Always true according to the connections as GPIO2 has been pulled HIGH
         {                      
              Serial.print("connecting to ");
              Serial.println(host);
              // Use WiFiClient class to create TCP connections
              WiFiClient client;
              const int httpPort = 80;
                if (!client.connect("192.168.4.1", httpPort)) {
                  Serial.println("connection failed");
                  return;
                   }    
              //Request to server to activate the led
              client.print(String("GET ") +"/Led"+" HTTP/1.1\r\n" + 
                           "Host: " + host + "\r\n" + 
                           "Connection: close\r\n\r\n");         
              delay(10);
              // Read all the lines of the reply from server and print them to Serial Monitor etc
              while(client.available()){
                String line = client.readStringUntil('\r');
                Serial.print(line);
              }
              //Close the Connection. Automatically
              Serial.println();
              Serial.println("closing connection");             
            }//End if

}//End Loop
