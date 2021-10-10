
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

  // ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // LEDs
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
}
void loop()
{
  unsigned long currentTime = millis(); //set up current time to arduino running time

  digitalWrite(trigPin, LOW);
  delay(1000);
  digitalWrite(trigPin, HIGH);
  delay(1000);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH); // returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;   // speed of sound wave divided by 2 (go and back)

  sittingTimeColor = GetSittingTimeColor(distance, currentTime);

  if (sittingTimeColor == "GREEN")
  {
    digitalWrite(LED_PIN_1, HIGH);
    digitalWrite(LED_PIN_2, LOW);
    digitalWrite(LED_PIN_3, LOW);
  }
  else if (sittingTimeColor == "YELLOW")
  {
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, HIGH);
    digitalWrite(LED_PIN_3, LOW);
  }
  else if (sittingTimeColor == "RED")
  {
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, LOW);
    digitalWrite(LED_PIN_3, HIGH);
  }

  delay(2000);
}
