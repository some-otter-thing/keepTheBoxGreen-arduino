void setupDisplay() {                                               // 128*160 matrix of pixel 
  tft.initR(INITR_BLACKTAB);                                        // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);                                     // fill screen with black color

  // topbar
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);                     // set text color to white and black background
  tft.setTextSize(1);                                               // set text size to 1
  tft.setCursor(85, 0);                                             // font starting coordinate of (x, y)  
  tft.print("online!");

  tft.drawFastHLine(0, 10,  tft.width(), ST7735_WHITE);             // draw horizontal white line at position (0, 30)

  // text block
  tft.setCursor(0, 17);
  tft.print("temp static content");

  tft.drawFastHLine(0, 30,  tft.width(), ST7735_WHITE);

  // temp
  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
  tft.setCursor(0, 40);
  tft.print("TEMPERATURE = 24C");

  // hum
  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
  tft.setCursor(0, 55);
  tft.print("HUMIDITY = 52%");

  // dust 
  tft.setTextColor(ST7735_RED, ST7735_BLACK);
  tft.setCursor(0, 70);
  tft.print("DUST LEVEL = BAD");

  // desk time
  tft.setTextColor(ST7735_RED, ST7735_BLACK);
  tft.setCursor(0, 85);
  tft.print("DESK TIME = 42:27");

  tft.drawFastHLine(0, 100,  tft.width(), ST7735_WHITE);

  // set text size of above 3 value
  tft.setTextSize(2);

  // set notification in half below
  tft.setTextColor(ST7735_RED, ST7735_BLACK);
  tft.setCursor(0, 115);
  tft.print("TAKE A BREAK!! :(");
  tft.setTextSize(3);
}
