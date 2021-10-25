void setupDust() {
  sds.begin();
  Serial.println(sds.queryFirmwareVersion().toString()); 
  Serial.println(sds.setActiveReportingMode().toString()); 
  Serial.println(sds.setContinuousWorkingPeriod().toString()); 
}

