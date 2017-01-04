// Serever is created to received commands through a direct socket
WiFiServer server(10002);
WiFiClient SocketClient;

String inputString = "";         // a string to hold incoming data
bool isChatEnabled;

void SocketServerSetup(void)
{
  isChatEnabled = false;
  // Init server
  server.begin();
}


String SocketServerUpdate(void)
{
  String ret = "";
  // listen for incoming SocketClients
  SocketClient = server.available();
  /* Sockets have higher priority */
  if (SocketClient) {
    while (SocketClient.available()) {
      // get the new byte:
      char inChar = (char)SocketClient.read();

      // if the incoming character is a newline, set a flag
      // so the main loop can do something about it:
      if (inChar == '\n') {
        ret = inputString;
        inputString = "";
      }
      else
      {
        // add it to the inputString:
        inputString += inChar;
      }
    }
  }
  return ret;
}

void SocketServerReply(String msg)
{
  if (isChatEnabled)
  {
    if (SocketClient)
    {
      if (SocketClient.connected())
      {
        SocketClient.println(msg);
      }
    }
  }
}

void SocketServerStop(void)
{
  if (SocketClient)
  {
    if (SocketClient.connected())
    {
      SocketClient.stop();
    }
  }
}

void SocketServerChatEnable(void)
{
  isChatEnabled = true;
}

void SocketServerChatDisable(void)
{
  isChatEnabled = false;
}
