
void DebugSetup(void)
{
  Serial.begin(115200);
}

void DebugPrint(String msg)
{
  Serial.print(msg);
}

void DebugPrintln(String msg)
{
  Serial.println(msg);
}

void DebugPrintln(int msg)
{
  Serial.println(msg);
}

