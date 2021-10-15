char* getSittingTimeColor(int distance, long currentTime)
{
  if (distance >= DISTANCE_THRESHOLD)
  {
    Serial.println("You are fine now! You are out of the table");
    previousTime = currentTime;
    timeSitting = 0;
    return "GREEN";
  }
  if (distance < DISTANCE_THRESHOLD)
  {
    timeSitting = currentTime - previousTime;
    if (timeSitting >= SITTING_TIME_GREEN && timeSitting < SITTING_TIME_YELLOW)
    {
      Serial.println("Focused work for ");
      Serial.print(timeSitting);
      Serial.println("\n------------");
      return "GREEN";
    }
    else if (timeSitting >= SITTING_TIME_YELLOW && timeSitting < SITTING_TIME_RED)
    {
      Serial.println("Warning! It is yellow, take a break soon");
      return "YELLOW";
    }
    else if (timeSitting >= SITTING_TIME_RED)
    {
       Serial.println("YOU NEED TO HAVE BREAK!!!!");
      return "RED";
    }
  }
}
