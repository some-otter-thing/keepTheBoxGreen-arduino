#include <ArduinoBearSSL.h>
#include <ArduinoECCX08.h>
#include <utility/ECCX08SelfSignedCert.h>
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

const char ssid[] = SECRET_SSID;
const char pass[] = SECRET_PASS;
const char broker[] = SECRET_BROKER;
String deviceId = SECRET_DEVICE_ID;

WiFiClient wifiClient;               // Used for the TCP socket connection
BearSSLClient sslClient(wifiClient); // Used for SSL/TLS connection
MqttClient mqttClient(sslClient);

unsigned long lastMillis = 0;

void setup()
{
  Serial.begin(9600); //Initialize serial and wait for port to open:
  while (!Serial);

  if (!ECCX08.begin())
  {
    Serial.println("No ECCX08 present!");
    while (1);
  }

  // reconstruct the self signed cert
  ECCX08SelfSignedCert.beginReconstruction(0, 8);
  ECCX08SelfSignedCert.setCommonName(ECCX08.serialNumber());
  ECCX08SelfSignedCert.endReconstruction();

  // Set a callback to get the current time
  // used to validate the servers certificate
  ArduinoBearSSL.onGetTime(getTime);

  // Set the ECCX08 slot to use for the private key
  // and the accompanying public certificate for it
  sslClient.setEccSlot(0, ECCX08SelfSignedCert.bytes(), ECCX08SelfSignedCert.length());

  // Set the client id used for MQTT as the device id
  mqttClient.setId(deviceId);

  // Set the username to "<broker>/<device id>/api-version=2018-06-30" and empty password
  String username;

  username += broker;
  username += "/";
  username += deviceId;
  username += "/api-version=2018-06-30";

  mqttClient.setUsernamePassword(username, "");

  mqttClient.onMessage(onMessageReceived); // called when the MQTTClient receives a message
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    connectWiFi();
  }

  if (!mqttClient.connected())
  {
    connectMQTT();
  }

  // poll for new MQTT messages and send keep alives
  mqttClient.poll();

  // publish a message roughly every 5 seconds.
  if (millis() - lastMillis > 5000)
  {
    lastMillis = millis();

    publishMessage();
  }
}

unsigned long getTime()
{
  return WiFi.getTime();
}

void connectWiFi()
{
  Serial.print("Attempting to connect to SSID: ");
  Serial.print(ssid);
  Serial.print(" ");

  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    Serial.print(".");
    delay(5000);
  }
  Serial.println();

  Serial.println("You're connected to the network");
  Serial.println();
}

void connectMQTT()
{
  Serial.print("Attempting to MQTT broker: ");
  Serial.print(broker);
  Serial.println(" ");

  while (!mqttClient.connect(broker, 8883))
  {
    Serial.print(".");
    Serial.println(mqttClient.connectError());
    delay(5000);
  }
  Serial.println();

  Serial.println("You're connected to the MQTT broker");
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe("devices/" + deviceId + "/messages/devicebound/#");
}

void publishMessage()
{
  Serial.println("Publishing message");

  // send message, the Print interface can be used to set the message contents
  mqttClient.beginMessage("devices/" + deviceId + "/messages/events/");
  mqttClient.print("hello ");
  mqttClient.print(millis());
  mqttClient.endMessage();
}

void onMessageReceived(int messageSize)
{
  // we received a message, print out the topic and contents
  Serial.print("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  // use the Stream interface to print the contents
  while (mqttClient.available())
  {
    Serial.print((char)mqttClient.read());
  }
  Serial.println();

  Serial.println();
}
