
#include <WiFiNINA.h>

#include "arduino_secrets.h"

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
  Serial.println("----------------------------------------");
  printData();
  Serial.println("----------------------------------------");
}
void loop()
{
  delay(10000);
  printData();
  Serial.println("----------------------------------------");
}
// keep this function for now
void printData()
{
  Serial.println("Board Information:");
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.println();
  Serial.println("Network Information:");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);
}
