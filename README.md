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

- Connecting to wifi - <a href="https://www.arduino.cc/en/Guide/MKRWiFi1010/connecting-to-wifi-network">link</a>

- Explanation of necessary drivers for the Arduino MKR1000 series of boards - <a href="https://www.arduino.cc/en/Guide/MKR1000">link</a>

- Helper to make json https://arduinojson.org/v6/assistant/

### Schematics & blueprint

- Use [fritzing](https://fritzing.org/) to open the file in blueprint folder
- Need to sign up if you don't want to pay for it..

### Used Hardwares:

1. Arduino MKR 1010 Board
2. DHT22 Sensor
3. HC-SR0 4Ultrasonic Sensor
4. Generic LED Strip
5. Generic 1.8" TFT Display
6. Nova PM SDS011 PM 2.5 sensor

![Fritzing breadboard hardware planning](https://i.imgur.com/iirBkXY.png)
![Fritzing schematics planning](https://i.imgur.com/qySSMSN.png)
### Used libraries:

1. Wifi:
   - WiFiNINA library
2. MQTT connection:
   - ArduinoMqttClient
   - ArduinoBearSSL
   - ArduinoECCX08
   - ArduinoJson
3. TFT Display
    * Adafruit_GFX
    * Adafruit_ST7735 & ST7798
    * Adafruit BusIO 
   - Adafruit_GFX
   - Adafruit_ST7735 & ST7798
4. DHT22
   - Adafruit DHT sensor library
5. LED
   - FastLED
6. Dust Sensor
   - Nova Fitness SDS dust sensors library
