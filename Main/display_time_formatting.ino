char* timeFormatting() {
  unsigned long second = timeSitting / 1000;
  unsigned long minute = second / 60;
  unsigned long hour = minute / 60;
  second %= 60;
  minute %= 60;
  hour %= 24;

  if (hour < 10) {
    tft.print('0');
  }
  tft.print(hour);
  tft.print(":");
  if (minute < 10) {
    tft.print('0');
  }
  tft.print(minute);
  tft.print(":");
  if (second < 10) {
    tft.print('0');
  }
  tft.print(second);
}
