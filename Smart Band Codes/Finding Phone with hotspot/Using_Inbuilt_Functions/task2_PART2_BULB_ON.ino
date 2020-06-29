/*
    This sketch demonstrates how to scan WiFi networks.
    The API is almost the same as with the WiFi Shield library,
    the most obvious difference being the different file you need to include:
*/
#include "ESP8266WiFi.h"

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  pinMode(16,OUTPUT);

}

void loop() {


  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();

  if (n == 0) {
    
  } else {

    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      
      if(WiFi.SSID(i)=="CMCC-Nithin")
      {digitalWrite(16,HIGH);
      
      delay(10);
      }
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
}
