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

// wifi
WiFiClient wifiClient;               // Used for the TCP socket connection
BearSSLClient sslClient(wifiClient); // Used for SSL/TLS connection
MqttClient mqttClient(sslClient);

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
const char broker[] = SECRET_BROKER;
String deviceId = SECRET_DEVICE_ID;

int status = WL_IDLE_STATUS;

// interfacing hum/temp sensor pins
DHT dht(DHTPIN, DHTTYPE);

CRGB leds[NUM_LEDS];
// interfacing display lib pins
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(9600);

  // display
  //  tft.initR(INITR_BLACKTAB);     // initialize a ST7735S chip, black tab
  //  tft.fillScreen(ST7735_BLACK);  // fill screen with black color
  //  tft.drawFastHLine(0, 30,  tft.width(), ST7735_WHITE);   // draw horizontal white line at position (0, 30)
  //  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  // set text color to white and black background
  //  tft.setTextSize(1);                 // text size = 1
  //  tft.setCursor(120, 0);               // move cursor to position (4, 0) pixel
  //  tft.print("@");
  //  tft.drawFastHLine(0, 7,  tft.width(), ST7735_WHITE);
  //  tft.setCursor(0, 15);              // move cursor to position (19, 15) pixel
  //  tft.print("okja is cute dog");
  //  tft.drawFastHLine(0, 76,  tft.width(), ST7735_WHITE);  // draw horizontal white line at position (0, 76)
  //  tft.drawFastHLine(0, 122,  tft.width(), ST7735_WHITE);  // draw horizontal white line at position (0, 122)
  //  tft.setTextColor(ST7735_RED, ST7735_BLACK);     // set text color to red and black background
  //  tft.setCursor(25, 39);              // move cursor to position (25, 39) pixel
  //  tft.print("TEMPERATURE =");
  //  tft.setTextColor(ST7735_CYAN, ST7735_BLACK);  // set text color to cyan and black background
  //  tft.setCursor(34, 85);              // move cursor to position (34, 85) pixel
  //  tft.print("HUMIDITY =");
  //  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);  // set text color to green and black background
  //  tft.setCursor(34, 131);              // move cursor to position (34, 131) pixel
  //  tft.print("PRESSURE =");
  //  tft.setTextSize(2);                 // text size = 2
  setupDisplay();


  while (!Serial);

  // wifi
  while (status != WL_CONNECTED) {
    setupWIFI();
  }
  Serial.println("You're connected to the network");
  printWiFiData(); // will be deleted

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
}
void loop() {
  unsigned long currentTime =
    millis();                 // set up current time to arduino running time
  unsigned long lastMillis = 0; // used for mqtt connection
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }
  if (!mqttClient.connected()) {
    connectMQTT();
  }
  // poll for new MQTT messages and send keep alives
  mqttClient.poll();

  digitalWrite(trigPin, LOW);
  delay(1000);
  digitalWrite(trigPin, HIGH);
  delay(1000);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(
               echoPin, HIGH); // returns the sound wave travel time in microseconds
  distance =
    duration * 0.034 / 2; // speed of sound wave divided by 2 (go and back)

  temp = dht.readTemperature();
  hum = dht.readHumidity();
  sittingTimeColor = getSittingTimeColor(distance, currentTime);
  tempColor = getTempColor(temp);
  humColor = getHumColor(hum);
  timeSitting = getSittingTime(distance, currentTime);
  // publish a message every 10 seconds.
  //  if (millis() - lastMillis > 10000) {
  //    lastMillis = millis();
  //    publishMessage();
  //  }

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
