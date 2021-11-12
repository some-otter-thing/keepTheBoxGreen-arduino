void getNotification() {
  tft.setTextSize(2);
  tft.setCursor(0, 105);
  if (sittingTimeColor == GREEN) {
    tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
    tft.print("Focus!             ");
  } else if (sittingTimeColor == YELLOW){
    tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
    tft.print("Easy...    ");
  } else {
    tft.setTextColor(ST7735_RED, ST7735_BLACK);
    tft.print("Take five!");
  }
}
