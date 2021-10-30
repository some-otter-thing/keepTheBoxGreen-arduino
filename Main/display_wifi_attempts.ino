void displayWIFIAttempts() {
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  tft.setTextSize(1);
  tft.setCursor(0, 40);
  tft.print("Attempts");
  tft.setCursor(0, 55);
  tft.print("to connect to WIFI:");
  tft.setTextSize(3);
  tft.setCursor(0, 70);
  tft.print("   ");
  tft.print(wifiRetries);
}
