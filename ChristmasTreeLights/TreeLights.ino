const int LEDGroup1 = 5;
const int LEDGroup2 = 4;

float LEDgroupIntensity1;
float LEDgroupIntensity2;
float LastLEDIntensity1;
float LastLEDIntensity2;
long startSequenceTime;

int currentSequence;

long variableTime;

void TreeLightsSetup(void)
{
  //Initialize global variables
  LEDgroupIntensity1 = 0.0;
  LEDgroupIntensity2 = 0.0;
  LastLEDIntensity1 = 0.0;
  LastLEDIntensity2 = 0.0;
  currentSequence = 0;

  // Set LED pin as outputs
  pinMode(LEDGroup1, OUTPUT);
  pinMode(LEDGroup2, OUTPUT);

  // Initialize outputs at Low level to power of the tree lights
  digitalWrite(LEDGroup1, LOW);
  digitalWrite(LEDGroup2, LOW);
}


void TreeLightStart(int sequence)
{
  if (sequence != currentSequence)
  {
    currentSequence = sequence;

    switch (sequence)
    {
      case 0:
        LEDgroupIntensity1 = 0.0;
        LEDgroupIntensity2 = 0.0;
        break;
      case 1:
        LEDgroupIntensity1 = 100.0;
        LEDgroupIntensity2 = 100.0;
        break;
      case 2:
        LEDgroupIntensity1 = 50.0;
        LEDgroupIntensity2 = 50.0;
        break;
      case 3:
        LEDgroupIntensity1 = 0.0;
        LEDgroupIntensity2 = 0.0;
        break;
      case 4:
        LEDgroupIntensity1 = 100.0;
        LEDgroupIntensity2 = 0.0;
        break;
      case 5:
        LEDgroupIntensity1 = 0.0;
        LEDgroupIntensity2 = 0.0;
        variableTime = 1000;
        break;
      case 6:
        variableTime = 0;
        LEDgroupIntensity1 = 0.0;
        LEDgroupIntensity2 = 0.0;
        break;
      default:
        break;
    }
    startSequenceTime = millis();
  }
}

void TreeLightsUpdate(void)
{
  /* This sequence must be non blocking */
  switch (currentSequence)
  {
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      if (millis() - startSequenceTime > 50)
      {
        LEDgroupIntensity1++;
        LEDgroupIntensity2++;

        if (LEDgroupIntensity1 > 100.0)
        {
          LEDgroupIntensity1 = 0.0;
        }
        if (LEDgroupIntensity2 > 100.0)
        {
          LEDgroupIntensity2 = 0.0;
        }
        startSequenceTime = millis();
      }
      break;
    case 4:
      if (millis() - startSequenceTime > 200)
      {
        if (LEDgroupIntensity1 == 0)
        {
          LEDgroupIntensity1 = 100.0;
          LEDgroupIntensity2 = 0.0;
        }
        else
        {
          LEDgroupIntensity1 = 0.0;
          LEDgroupIntensity2 = 100.0;
        }
        startSequenceTime = millis();
      }
      break;
    case 5:
      if (millis() - startSequenceTime > variableTime)
      {
        if (LEDgroupIntensity1 == 0.0)
        {
          LEDgroupIntensity1 = 100.0;
          LEDgroupIntensity2 = 0.0;
        }
        else
        {
          LEDgroupIntensity1 = 0.0;
          LEDgroupIntensity2 = 100.0;
        }

        variableTime -= 10;

        if (variableTime == 50)
        {
          variableTime = 1000;
        }
        startSequenceTime = millis();
      }
      break;
    case 6:
      if (millis() - startSequenceTime > 200)
      {
        if ((variableTime < 10) && (variableTime > 0))
        {
          if (LEDgroupIntensity1 == 0.0)
          {
            LEDgroupIntensity1 = 100.0;
            LEDgroupIntensity2 = 0.0;
          }
          else
          {
            LEDgroupIntensity1 = 0.0;
            LEDgroupIntensity2 = 0.0;
          }
        }
        else if ((variableTime < 20) && (variableTime > 10))
        {
          if (LEDgroupIntensity2 == 0.0)
          {
            LEDgroupIntensity1 = 0.0;
            LEDgroupIntensity2 = 1000.0;
          }
          else
          {
            LEDgroupIntensity1 = 0.0;
            LEDgroupIntensity2 = 0.0;
          }
        }
        else
        {
          if (LEDgroupIntensity1 == 0.0)
          {
            LEDgroupIntensity1 = 100.0;
            LEDgroupIntensity2 = 0.0;
          }
          else
          {
            LEDgroupIntensity1 = 0.0;
            LEDgroupIntensity2 = 100.0;
          }
        }
        variableTime++;
        if (variableTime == 50)
        {
          variableTime = 0;
        }
        startSequenceTime = millis();
      }
      break;
    default:
      break;
  }

  TreeLightsWrite(LEDgroupIntensity1, LEDgroupIntensity2);
}


void TreeLightsWrite(float LEDgroupIntensity1, float LEDgroupIntensity2)
{
  if (LEDgroupIntensity1 != LastLEDIntensity1)
  {
    if (LEDgroupIntensity1 == 100.0)
    {
      analogWrite(LEDGroup1, 255);
    }
    else if (LEDgroupIntensity1 == 0.0)
    {
      analogWrite(LEDGroup1, 0);
    }
    else
    {
      analogWrite(LEDGroup1, 50);
    }
    LastLEDIntensity1 = LEDgroupIntensity1;
  }

  if (LEDgroupIntensity2 != LastLEDIntensity2)
  {
    if (LEDgroupIntensity2 == 100.0)
    {
      analogWrite(LEDGroup2, 255);
    }
    else if (LEDgroupIntensity2 == 0.0)
    {
      analogWrite(LEDGroup2, 0);
    }
    else
    {
      analogWrite(LEDGroup2, 50);
    }
    LastLEDIntensity2 = LEDgroupIntensity2;
  }
}
