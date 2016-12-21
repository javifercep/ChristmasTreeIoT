/*
  Christmas Tree lights

  This sketch is able to control the Christmas lights of Christmas tree based on the commands sent
  through the network.

  created 10 Dec 2016
  by Javier Fernández <jfercep@gmail.com>


  based on this example from Arduino guys:

  http://arduino.cc/en/Tutorial/WiFiRTC
*/

#include <WiFi101.h>
#include <WiFiUdp.h>
#include <RTCZero.h>

//#define DEBUG

RTCZero rtc;

char ssid[] = "yourSSID";       //  your network SSID (name)
char pass[] = "yourPassword";   // your network password
int keyIndex = 0;               // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

const int GMT = 1; //change this to adapt it to your time zone

void setup() {

  // Init digital outputs for HeartBeat and LEDs
  HeartbeatInit(500);
  TreeLightsSetup();

#ifdef DEBUG
  DebugSetup();
#endif

  WiFiSetup();
  SocketServerSetup();
  WebClientSetup(1000);
}

void loop() {

  String command;
  String WebClientCommand;
  String SocketServerCommand;

  WebClientCommand = WebClientUpdate();
  SocketServerCommand = SocketServerUpdate();

  if (WebClientCommand != "")
  {
    command = WebClientCommand;
  }

  // Sockets have higher priority
  if (SocketServerCommand != "")
  {
    command = SocketServerCommand;
  }


  if (command != "")
  {
    switch (command.charAt(0))
    {
      case 'a':
        HeartBeatSetBeat(200);
        SocketServerReply("I'm Alife & crazy!");
        break;
      case 'b':
        HeartBeatSetBeat(500);
        SocketServerReply("I'm Alife!");
        break;
      case 'c':
        TreeLightStart(0);
        SocketServerReply("I'm off!");
        break;
      case 'd':
        TreeLightStart(1);
        SocketServerReply("I'm on!");
        break;
      case 'e':
        TreeLightStart(2);
        SocketServerReply("I'm in some state!");
        break;
      case 'f':
        TreeLightStart(3);
        SocketServerReply("Relaxed sequence!");
        break;
      case 'g':
        TreeLightStart(4);
        SocketServerReply("Simple sequence!");
        break;
      case 'h':
        TreeLightStart(5);
        SocketServerReply("Uuuuuuuaaaaah!");
        break;
      case 'i':
        TreeLightStart(6);
        SocketServerReply("I don't know what I'm doing...");
        break;
      case 'j':
        WebClientEnabled();
        break;
      case 'k':
        WebClientDisabled();
        break;
      case 'x':
        // close the connection:
        SocketServerStop();
        break;
      default:
        break;
    }
  }
  TreeLightsUpdate();
  HeartbeatUpdate();
}

void WiFiSetup(void)
{
  // check if the WiFi module works
  if (WiFi.status() == WL_NO_SHIELD) {
#ifdef DEBUG
    DebugPrintln("WiFi shield not present");
#endif
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {

#ifdef DEBUG
    DebugPrint("Attempting to connect to SSID: ");
    DebugPrintln(ssid);
#endif
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }


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
    DebugPrint("NTP unreachable!!");
#endif
    while (1);
  }
  else {

#ifdef DEBUG
    DebugPrint("Epoch received: ");
    DebugPrintln(epoch);
#endif
    rtc.setEpoch(epoch);

#ifdef DEBUG
    DebugPrint();
#endif
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

