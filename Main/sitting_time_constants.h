const int DISTANCE_THRESHOLD = 50;
const unsigned long SITTING_TIME_GREEN = 2000; // 30 min * 60 000 = 1800000;
const unsigned long SITTING_TIME_YELLOW = 5000; // 45 min  = 2700000;
const unsigned long SITTING_TIME_RED = 10000; // 60 min = 3600000
unsigned long previousTime = 0;
unsigned long timeSitting = 0;