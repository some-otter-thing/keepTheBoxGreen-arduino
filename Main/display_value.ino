void displayValue() {

  // topbar
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);                     // set text color to white and black background
  tft.setTextSize(1);                                               // set text size to 1
  tft.setCursor(85, 0);                                             // font starting coordinate of (x, y)
  tft.print(onlineStatus());

  // text block
  tft.setTextSize(1);
  tft.setCursor(0, 17);
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  tft.print("only works if online");

  tft.setTextSize(1);

  // temp
  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
  tft.setCursor(0, 40);
  tft.print("Temperature = ");
  tft.print(temp);
  tft.print("C");

  // hum
  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
  tft.setCursor(0, 55);
  tft.print("Humidity    = ");
  tft.print(hum);
  tft.print("%");

  // dust
  tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
  tft.setCursor(0, 70);
  tft.print("Dust Level  = ");
  tft.print("N/A");

  // desk time
  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
  tft.setCursor(0, 85);
  tft.print("Desk Time   = ");
  tft.print(timeSitting / 1000);

  // set notification in half below
  getNotification();
}

char* onlineStatus() {
  if (WiFi.status() == WL_CONNECTED) {
    return "Online";
  } else {
    return "Offline";
  }
}
