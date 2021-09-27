### KeepTheBoxGreen device implementation


### Guides:

Connecting to wifi  - <a href="https://www.arduino.cc/en/Guide/MKRWiFi1010/connecting-to-wifi-network">link</a>

Explanation of necessary drivers for the Arduino MKR1000 series of boards - <a href="https://www.arduino.cc/en/Guide/MKR1000">link</a>

### To connect to wifi

1. Create a header file within Main folder
```
touch arduino_secrets.h
```
2. Add information about wifi:
```
#define SECRET_SSID "here is network name"
#define SECRET_PASS "here is the password of wifi"
```
