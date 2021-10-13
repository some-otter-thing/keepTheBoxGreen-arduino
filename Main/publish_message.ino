void publishMessage()
{
  Serial.println("Publishing message");

  doc["connectionDeviceId"] = "keep-the-box-green-device";
  doc["connectionDeviceGenerationId"] = "637669621042053570";
  doc["eventTimestamp"] = "637669621042053570";
  doc["temperature"] = temp;
  doc["humidity"] = hum;
  doc["dustConcentration"] = 64.8;

  // TODO: can be removed, it serializes the document in the serial monitor
  serializeJson(doc, Serial);
  Serial.println(" ");

  char payload[1024];
  size_t payloadSize = serializeJson(doc, payload);

  mqttClient.beginMessage("devices/" + deviceId + "/messages/events/", static_cast<unsigned long>(payloadSize));
  mqttClient.print(payload);
  mqttClient.endMessage();
