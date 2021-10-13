unsigned long getTime()
{
  return WiFi.getTime();
}


void setupMQTT()
{
    if (!ECCX08.begin())
    {
        Serial.println("No ECCX08 present!");
        while (1)
            ;
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