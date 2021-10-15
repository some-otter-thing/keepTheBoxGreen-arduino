int getSittingTime(int distance, long currentTime)
{
    if (distance >= DISTANCE_THRESHOLD)
    {
        previousTime = currentTime;
        timeSitting = 0;
        return timeSitting;
    }
    if (distance < DISTANCE_THRESHOLD)
    {
        timeSitting = currentTime - previousTime;
        return timeSitting;
    }
}