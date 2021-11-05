#include <ArduinoBearSSL.h>
#include <ArduinoECCX08.h>
#include <ArduinoMqttClient.h>
#include <ArduinoJson.h>
#include <utility/ECCX08SelfSignedCert.h>

#include <WiFiNINA.h>

#include "arduino_secrets.h"
#include "display_constants.h"
#include "main_constants.h"
#include "sitting_time_constants.h"
#include <DHT.h>
#include <FastLED.h>

// importing display lib
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// dust sensor
#include "SdsDustSensor.h"

// wifi
WiFiClient wifiClient;               // Used for the TCP socket connection
BearSSLClient sslClient(wifiClient); // Used for SSL/TLS connection
MqttClient mqttClient(sslClient);

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
const char broker[] = SECRET_BROKER;
String deviceId = SECRET_DEVICE_ID;

int status = WL_IDLE_STATUS;
int wifiRetries = 0;
int mqttRetries = 0;
unsigned long timeWIFISetUpAttempt;
// interfacing hum/temp sensor pins
DHT dht(DHTPIN, DHTTYPE);

CRGB leds[NUM_LEDS];
// interfacing display lib pins
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// dust sensor
SdsDustSensor sds(Serial1);

void setup() {
  Serial.begin(9600);


  while (!Serial);
  // display
  setupDisplay();

  // wifi connect try for MAX_WIFI_RETRIES times
  while (status != WL_CONNECTED && (wifiRetries < MAX_WIFI_RETRIES)) {
    setupWIFI();
    displayWIFIAttempts();
    timeWIFISetUpAttempt = millis(); // used to check wifi connection
  }
  if (status == WL_CONNECTED) {
    Serial.println("You're connected to the network");
    printWiFiData();
    wifiRetries = 0;
  }
  // mqtt
  setupMQTT();

  // temperature and humdity
  dht.begin();
  // ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // LEDs
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  // dust sensor
  setupDust();
}

void loop() {
  unsigned long currentTime =
    millis();                 // set up current time to arduino running time
  unsigned long lastMillis = 0; // used for mqtt connection


  if (WiFi.status() != WL_CONNECTED && (millis() - timeWIFISetUpAttempt) > 1800000) {
    wifiRetries = 0;
    connectWiFi();
    timeWIFISetUpAttempt =   millis();
  }
  // TODO: Implement same retry logic as for wifi 
  if (!mqttClient.connected() && WiFi.status() == WL_CONNECTED) {
    connectMQTT();
    // poll for new MQTT messages and send keep alives
    mqttClient.poll();
  }

  digitalWrite(trigPin, LOW);
  delay(500);
  digitalWrite(trigPin, HIGH);
  delay(500);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(
               echoPin, HIGH); // returns the sound wave travel time in microseconds
  distance =
    duration * 0.034 / 2; // speed of sound wave divided by 2 (go and back)

  temp = dht.readTemperature();
  hum = dht.readHumidity();
  PmResult pm = sds.readPm();
  dust = pm.pm25;

  sittingTimeColor = getSittingTimeColor(distance, currentTime);
  tempColor = getTempColor(temp);
  humColor = getHumColor(hum);
  dustColor = getDustColor(dust);
  timeSitting = getSittingTime(distance, currentTime);


  // publish a message every 10 seconds.
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();
    publishMessage();
  }

  if (sittingTimeColor == GREEN && tempColor == GREEN && humColor == GREEN && dustColor == GREEN)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB(0, 255, 0);
      FastLED.show();
    }
  }
  else if (sittingTimeColor == RED || tempColor == RED || humColor == RED || dustColor == RED)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB(255, 0, 0);
      FastLED.show();
    }
  }
  else if (sittingTimeColor == YELLOW || tempColor == YELLOW || humColor == YELLOW || dustColor == YELLOW)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB(255, 255, 0);
      FastLED.show();
    }
  }

  // display
  displayValue();

  // delay(1000);
}
