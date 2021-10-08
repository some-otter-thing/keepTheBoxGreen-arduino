
#include <WiFiNINA.h>

#include "arduino_secrets.h"
#include "main_constants.h"

char ssid[] = SECRET_SSID;   
char pass[] = SECRET_PASS;   
int status = WL_IDLE_STATUS; 

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to network: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  Serial.println("You're connected to the network");
  printWiFiData();
}
void loop()
{
  delay(10000);
}
