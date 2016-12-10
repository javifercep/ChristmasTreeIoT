/*
  Christmas Tree lights

  This sketch is able to control the Christmas lights of Christmas tree based on the commands sent
  through the network.

  created 10 Dec 2016
  by Javier Fernández <jfercep@gmail.com>


  basaed on this example from Arduino guys:

  http://arduino.cc/en/Tutorial/WiFiRTC
*/

#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>
#include <RTCZero.h>

//#define DEBUG

const int IsAlife = 6;
const int LEDGroup1 = 5;
const int LEDGroup2 = 4;

RTCZero rtc;

char ssid[] = "yourSSID";       //  your network SSID (name)
char pass[] = "yourPassword";   // your network password
int keyIndex = 0;               // your network key Index number (needed only for WEP)
long startAlifeTime;
long startSequenceTime;
long alifeTime = 500;
int status = WL_IDLE_STATUS;
int sequence;
int LedAnalogValue1;
int LedAnalogValue2;
int LedAnalogLastValue1;
int LedAnalogLastValue2;
int Count3;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete


WiFiServer server(10002);

const int GMT = 1; //change this to adapt it to your time zone

void setup() {
  pinMode(LEDGroup1, OUTPUT);
  pinMode(LEDGroup2, OUTPUT);
  pinMode(IsAlife, OUTPUT);

  digitalWrite(IsAlife, HIGH);
  digitalWrite(LEDGroup1, LOW);
  digitalWrite(LEDGroup2, LOW);

#ifdef DEBUG
  Serial.begin(115200);
#endif

  // check if the WiFi module works
  if (WiFi.status() == WL_NO_SHIELD) {
#ifdef DEBUG
    Serial.println("WiFi shield not present");
#endif
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {

#ifdef DEBUG
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
#endif
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  // Init server
  server.begin();

#ifdef DEBUG
  // you're connected now, so print out the status:
  printWiFiStatus();
#endif

  rtc.begin();

  unsigned long epoch;
  int numberOfTries = 0, maxTries = 6;
  do {
    epoch = WiFi.getTime();
    numberOfTries++;
  }
  while ((epoch == 0) || (numberOfTries > maxTries));

  if (numberOfTries > maxTries) {

#ifdef DEBUG
    Serial.print("NTP unreachable!!");
#endif
    while (1);
  }
  else {

#ifdef DEBUG
    Serial.print("Epoch received: ");
    Serial.println(epoch);
#endif
    rtc.setEpoch(epoch);

#ifdef DEBUG
    Serial.println();
#endif
  }
  startAlifeTime = millis();
  sequence = 0;
  LedAnalogValue1 = 0;
  LedAnalogValue2 = 0;
  LedAnalogLastValue1 = 0;
  LedAnalogLastValue2 = 0;
}

void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();

  if (client) {
    while (client.available()) {
      // get the new byte:
      char inChar = (char)client.read();

      // if the incoming character is a newline, set a flag
      // so the main loop can do something about it:
      if (inChar == '\n') {
        stringComplete = true;
      }
      else
      {
        // add it to the inputString:
        inputString += inChar;
      }
    }

    if (stringComplete)
    {
      switch (inputString.charAt(0))
      {
        case 'a':
          alifeTime = 200;
          client.println("I'm Alife & crazy!");
          break;
        case 'b':
          alifeTime = 500;
          client.println("I'm Alife!");
          break;
        case 'c':
          sequence = 0;
          LedAnalogValue1 = 0;
          LedAnalogValue2 = 0;
          client.println("I'm off!");
          break;
        case 'd':
          sequence = 0;
          LedAnalogValue1 = 255;
          LedAnalogValue2 = 255;
          client.println("I'm on!");
          break;
        case 'e':
          sequence = 0;
          LedAnalogValue1 = 128;
          LedAnalogValue2 = 128;
          client.println("I'm in some state!");
          break;
        case 'f':
          sequence = 1;
          LedAnalogValue1 = 0;
          LedAnalogValue2 = 0;
          startSequenceTime = millis();
          client.println("Relaxed sequence!");
          break;
        case 'g':
          sequence = 2;
          LedAnalogValue1 = 255;
          LedAnalogValue2 = 0;
          startSequenceTime = millis();
          client.println("Simple sequence!");
          break;
        case 'h':
          sequence = 3;
          Count3 = 0;
          startSequenceTime = millis();
          client.println("Uuuuuuuaaaaah!");
          break;
        case 'i':
          sequence = 4;
          LedAnalogValue1 = 0;
          LedAnalogValue2 = 0;
          startSequenceTime = millis();
          client.println("I don't know what I'm doing...");
          break;
        case 'x':
          // close the connection:
          client.stop();
          break;
        default:
          break;
      }
      startSequenceTime = millis();
      inputString = "";
      stringComplete = false;
    }
  }
  /* This sequence must be non blocking */
  switch (sequence)
  {
    case 1:
      if (millis() - startSequenceTime > 50)
      {
        LedAnalogValue1++;
        LedAnalogValue2++;

        if (LedAnalogValue1 > 255)
        {
          LedAnalogValue1 = 0;
        }
        if (LedAnalogValue2 > 255)
        {
          LedAnalogValue2 = 0;
        }
        startSequenceTime = millis();
      }
      break;
    case 2:
      if (millis() - startSequenceTime > 500)
      {
        if (LedAnalogValue1 == 0)
        {
          LedAnalogValue1 = 255;
          LedAnalogValue2 = 0;
        }
        else
        {
          LedAnalogValue1 = 0;
          LedAnalogValue2 = 255;
        }
        startSequenceTime = millis();
      }
      break;
    case 3:
      if (millis() - startSequenceTime > 100)
      {
        switch (Count3)
        {
          case 0:
            LedAnalogValue1 = 100;
            LedAnalogValue2 = 200;
            Count3++;
            break;
          case 1:
            LedAnalogValue1 = 255;
            LedAnalogValue2 = 50;
            Count3++;
            break;
          case 2:
            LedAnalogValue1 = 200;
            LedAnalogValue2 = 100;
            Count3++;
            break;
          case 3:
            LedAnalogValue1 = 200;
            LedAnalogValue2 = 255;
            Count3 = 0;
            break;
          default:
            Count3 = 0;
            break;
        }
        startSequenceTime = millis();
      }
      break;
    case 4:
      if (millis() - startSequenceTime > 200)
      {
        LedAnalogValue1 += 16;
        LedAnalogValue2 -= 25;

        if (LedAnalogValue1 > 255)
        {
          LedAnalogValue1 = 0;
        }
        if (LedAnalogValue2 < 0)
        {
          LedAnalogValue2 = 255;
        }
        startSequenceTime = millis();
      }
      break;
    default:
      break;
  }

  if (LedAnalogValue1 != LedAnalogLastValue1)
  {
    LedAnalogLastValue1 = LedAnalogValue1;
    analogWrite(LEDGroup1, LedAnalogValue1);
  }

  if (LedAnalogValue2 != LedAnalogLastValue2)
  {
    LedAnalogLastValue2 = LedAnalogValue2;
    analogWrite(LEDGroup2, LedAnalogValue2);
  }
  /* Alife LED */
  if (millis() - startAlifeTime > alifeTime)
  {
    digitalWrite(IsAlife, digitalRead(IsAlife) ^ 1);
    startAlifeTime = millis();
  }
}

#ifdef DEBUG
void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
#endif
