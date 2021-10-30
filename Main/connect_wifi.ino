void connectWiFi()
{
  Serial.print("Attempting to connect to SSID: ");
  Serial.print(ssid);
  Serial.print(" ");

  while (WiFi.begin(ssid, pass) != WL_CONNECTED && wifiRetries < MAX_WIFI_RETRIES)
  {
    wifiRetries ++;
    timeWIFISetUpAttempt =   millis(); // used to check wifi connection
    Serial.print(".");
    delay(2000);
  }
}
