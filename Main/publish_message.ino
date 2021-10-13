void publishMessage()
{
    Serial.println("Publishing message");

    // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage("devices/" + deviceId + "/messages/events/");
    mqttClient.print("hello ");
    mqttClient.print(millis());
    mqttClient.endMessage();
}