### KeepTheBoxGreen device implementation

The board uses Azure cloud IOT hub for storing messages.
### For local development:

1. Create a header file within Main folder
```
touch arduino_secrets.h
```
2. Add information about wifi:
```
#define SECRET_SSID "here is network name"
#define SECRET_PASS "here is the password of wifi"
#define SECRET_BROKER    ""
#define SECRET_DEVICE_ID ""
```

### Guides:

* Connecting to wifi  - <a href="https://www.arduino.cc/en/Guide/MKRWiFi1010/connecting-to-wifi-network">link</a>

* Explanation of necessary drivers for the Arduino MKR1000 series of boards - <a href="https://www.arduino.cc/en/Guide/MKR1000">link</a>

* Helper to make json https://arduinojson.org/v6/assistant/
### Used libraries:
1. Wifi:
    * WiFiNINA library
2. MQTT connection:
    * ArduinoMqttClient
    * ArduinoBearSSL
    * ArduinoECCX08
    * ArduinoJson
3. TFT Display
    * Adafruit_GFX
    * Adafruit_ST7735 & ST7798
    * Adafruit BusIO 
4. DHT22
    * Adafruit DHT sensor library
5. LED
    * FastLED
