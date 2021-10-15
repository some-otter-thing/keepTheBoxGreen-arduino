//void testdrawtext(char *text, uint16_t color) {
//  tft.setCursor(0, 0);
//  tft.setTextColor(color);
//  tft.setTextWrap(true);
//  tft.print(text);
//}


void setupDisplay() {
  tft.initR(INITR_BLACKTAB);     // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);  // fill screen with black color
  tft.drawFastHLine(0, 30,  tft.width(), ST7735_WHITE);   // draw horizontal white line at position (0, 30)
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  // set text color to white and black background
  tft.setTextSize(1);                 // text size = 1
  tft.setCursor(120, 0);               // move cursor to position (4, 0) pixel
  tft.print("@");
  tft.drawFastHLine(0, 7,  tft.width(), ST7735_WHITE);
  tft.setCursor(0, 15);              // move cursor to position (19, 15) pixel
  tft.print("some description");
  tft.drawFastHLine(0, 76,  tft.width(), ST7735_WHITE);  // draw horizontal white line at position (0, 76)
  tft.drawFastHLine(0, 122,  tft.width(), ST7735_WHITE);  // draw horizontal white line at position (0, 122)
  tft.setTextColor(ST7735_RED, ST7735_BLACK);     // set text color to red and black background
  tft.setCursor(25, 39);              // move cursor to position (25, 39) pixel
  tft.print("TEMPERATURE =");
  tft.setTextColor(ST7735_CYAN, ST7735_BLACK);  // set text color to cyan and black background
  tft.setCursor(34, 85);              // move cursor to position (34, 85) pixel
  tft.print("HUMIDITY =");
  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);  // set text color to green and black background
  tft.setCursor(34, 131);              // move cursor to position (34, 131) pixel
  tft.print("PRESSURE =");
  tft.setTextSize(2);                 // text size = 2
}
