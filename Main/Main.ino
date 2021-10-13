#include <ArduinoBearSSL.h>
#include <ArduinoECCX08.h>
#include <ArduinoMqttClient.h>
#include <utility/ECCX08SelfSignedCert.h>

#include <WiFiNINA.h>

#include "arduino_secrets.h"
#include "display_constants.h"
#include "main_constants.h"
#include <DHT.h>

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

// interfacing display lib pins
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(9600);

  // init display
  tft.initR(INITR_BLACKTAB); // Init ST7735S chip, black tab
  Serial.println(F("Initialized"));
  // text test printing
  tft.fillScreen(ST77XX_BLACK);
  testdrawtext("this is static text"
               "from setup block",
               ST77XX_WHITE);
  delay(1000);

  while (!Serial)
    ;

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
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
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

  // publish a message every 5 seconds.
  if (millis() - lastMillis > 5000) {
    lastMillis = millis();
    publishMessage(); // temp, hum, sittingTimeColor, dustConcentration will be
                      // published here
  }

  if (sittingTimeColor == GREEN && tempColor == GREEN && humColor == GREEN) {
    digitalWrite(LED_PIN_1, HIGH);
    digitalWrite(LED_PIN_2, LOW);
    digitalWrite(LED_PIN_3, LOW);
  } else if (sittingTimeColor == RED || tempColor == RED || humColor == RED) {
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, LOW);
    digitalWrite(LED_PIN_3, HIGH);
  } else if (sittingTimeColor == YELLOW || tempColor == YELLOW ||
             humColor == YELLOW) {
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, HIGH);
    digitalWrite(LED_PIN_3, LOW);
  }

  delay(2000);
}
