void getNotification() {
  tft.setTextSize(2);
  tft.setTextColor(ST7735_RED, ST7735_BLACK);
  tft.setCursor(0, 105);
  tft.print("TAKE A BREAK!!! :(");
}
