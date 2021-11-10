char* sittingTimeColor = "GREEN";
char* tempColor = "GREEN";
char* humColor = "GREEN";
char* dustColor = "GREEN";

char* GREEN = "GREEN";
char* YELLOW = "YELLOW";
char* RED = "RED";

// ultrasonic sensor
#define echoPin   5
#define trigPin   0

// led
#define LED_PIN 4
#define NUM_LEDS 100
#define BRIGHTNESS 50

// dht22
#define DHTPIN    1
#define DHTTYPE DHT22

// display 
#define TFT_CS   6
#define TFT_RST -1
#define TFT_DC   7
#define TFT_SCLK 9
#define TFT_MOSI 8

// humidifier
#define Atomizer 12 

long duration;
int distance;
float hum;
float temp;
float dust;

// wifi

#define MAX_WIFI_RETRIES 2
#define MAX_MQTT_RETRIES 2
