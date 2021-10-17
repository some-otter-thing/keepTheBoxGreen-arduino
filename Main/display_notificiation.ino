void getNotification() {
  tft.setTextSize(3);
  tft.setCursor(0, 105);
  if (sittingTimeColor == GREEN) {
    tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
    tft.print("Good!        ");
  } else if (sittingTimeColor == YELLOW){
    tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
    tft.print("Focusing..   ");
  } else {
    tft.setTextColor(ST7735_RED, ST7735_BLACK);
    tft.print("Take a break!");
  }
}
