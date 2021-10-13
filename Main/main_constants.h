char* sittingTimeColor = "GREEN";
char* tempColor = "GREEN";
char* humColor = "GREEN";

char* GREEN = "GREEN";
char* YELLOW = "YELLOW";
char* RED = "RED";

// ultrasonic sensor
#define echoPin   5
#define trigPin   0

// led
#define LED_PIN_1 2
#define LED_PIN_2 3
#define LED_PIN_3 4

// dht22
#define DHTPIN    1
#define DHTTYPE DHT22

// display 
#define TFT_CS   6
#define TFT_RST -1
#define TFT_DC   7
#define TFT_SCLK 9
#define TFT_MOSI 8

long duration;
int distance;
float hum;
float temp;
