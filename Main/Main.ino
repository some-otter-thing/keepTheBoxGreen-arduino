
#include <WiFiNINA.h>

#include "arduino_secrets.h"
#include "main_constants.h"
#include <DHT.h>

#include <FastLED.h>

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int status = WL_IDLE_STATUS;
DHT dht(DHTPIN, DHTTYPE);
CRGB leds[NUM_LEDS]; //

void setup()
{
  Serial.begin(9600);
  //  while (!Serial);
  //  while (status != WL_CONNECTED)
  //  {
  //    Serial.print("Attempting to connect to network: ");
  //    Serial.println(ssid);
  //    status = WiFi.begin(ssid, pass);
  //    delay(10000);
  //  }
  //  Serial.println("You're connected to the network");
  //  printWiFiData();

  // temperature and humdity
  dht.begin();
  // ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // LEDs
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
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

  temp = dht.readTemperature();
  hum = dht.readHumidity();
  sittingTimeColor = getSittingTimeColor(distance, currentTime);
  tempColor = getTempColor(temp);
  humColor = getHumColor(hum);

  if (sittingTimeColor == GREEN && tempColor == GREEN && humColor == GREEN)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB(0, 255, 0);
      FastLED.show();
    }
  }
  else if (sittingTimeColor == RED || tempColor == RED || humColor == RED)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB(255, 0, 0);
      FastLED.show();
    }
  }
  else if (sittingTimeColor == YELLOW || tempColor == YELLOW || humColor == YELLOW)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB(255, 255, 0);
      FastLED.show();
    }
  }
  delay(2000);
}
