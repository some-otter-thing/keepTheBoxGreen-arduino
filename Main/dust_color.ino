char* getDustColor(float dust){
  if(dust >= 0 && dust < 70) {
    Serial.print("Dust Concentration: ");
    Serial.print(dust);
    Serial.println("μg/m3");
    Serial.println("Air quality good");
    return "GREEN";
  } else if ( dust >= 70 && dust < 150) {
    Serial.print("Dust Concentration: ");
    Serial.print(dust);
    Serial.println("μg/m3");
    Serial.println("Air quality moderate");
    return "YELLOW";
  } else {
    Serial.print("Dust Concentration: ");
    Serial.print(dust);
    Serial.println("μg/m3");
    Serial.println("Air quality bad");
    return "RED";
  }
}
