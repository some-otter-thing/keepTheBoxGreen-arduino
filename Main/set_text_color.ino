void setTextColor(char* color){
  if (color == "GREEN"){
    tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
  } else if (color == "YELLOW"){
    tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
  } else {
    tft.setTextColor(ST7735_RED, ST7735_BLACK);
  }  
}
