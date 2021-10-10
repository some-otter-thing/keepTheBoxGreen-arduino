#include "temp_constants.h"

char* getTempColor(float temp) {
  if (temp >= BASELINE_TEMP - 2 && temp < BASELINE_TEMP + 2) {
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    Serial.println("Adequate temperature for work");
    return "GREEN";
  } else if (temp >= BASELINE_TEMP - 5 && temp < BASELINE_TEMP + 5) {
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    Serial.println("Whatever temperature for work");
    return "YELLOW";
  } else {
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    Serial.println("Bad temperature for work");
    return "RED";
  }
}
