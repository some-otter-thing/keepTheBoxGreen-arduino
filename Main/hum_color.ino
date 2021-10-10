#include "hum_constants.h"

char* getHumColor(float hum) {
  if (hum >= BASELINE_HUM - 15 && hum < BASELINE_HUM + 15) {
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.println("%");
    Serial.println("Adequate humidity for work");
    return "GREEN";
  } else if (hum >= BASELINE_HUM - 30 && hum < BASELINE_HUM + 30) {
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.println(" %");
    Serial.println("Whatever humidity for work");
    return "YELLOW";
  } else {
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.println(" %");
    Serial.println(" Bad humidity for work");
    return "RED";
  }
}
