const int IsAlife = 6;

long startTime;
int beatTime;

void HeartbeatInit(int milliseconds)
{
  pinMode(IsAlife, OUTPUT);
  digitalWrite(IsAlife, HIGH);
  beatTime = milliseconds;
  startTime = millis();
}

void HeartBeatSetBeat(int milliseconds)
{
  beatTime = milliseconds;
  startTime = millis();
}

void HeartbeatUpdate(void)
{
  if (millis() - startTime > beatTime)
  {
    digitalWrite(IsAlife, digitalRead(IsAlife) ^ 1);
    startTime = millis();
  }
}

