void setupDisplay() {                                               // 128*160 matrix of pixel
  // display init and fill bg black
  tft.initR(INITR_BLACKTAB);                                        // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);                                     // fill screen with black color

  // divider
  tft.drawFastHLine(0, 10,  tft.width(), ST7735_WHITE);             // draw horizontal white line at position (0, 30)
  tft.drawFastHLine(0, 30,  tft.width(), ST7735_WHITE);
  tft.drawFastHLine(0, 100,  tft.width(), ST7735_WHITE);

}
