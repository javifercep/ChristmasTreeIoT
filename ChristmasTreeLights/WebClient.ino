long pollTime;
long startPollTime;

String httpCommand = "";
boolean httpCommandComplete = false;

boolean pollingEnabled;
boolean requestInProgress;

long LocalTimeout;

char command[] = "www.javisfryingchips.com";    // name address for Google (using DNS)

// Initialize the Ethernet SocketClient library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient WebSocketClient;

void WebClientSetup(int pollingTime)
{
  pollingEnabled = false;
  requestInProgress = false;
  pollTime = pollingTime;
  startPollTime = millis();
}

String WebClientUpdate(void)
{
  String ret = "";

  if (millis() - startPollTime > pollTime)
  {
    if (pollingEnabled && !requestInProgress)
    {
#ifdef DEBUG
      SocketClient.println("\nStarting connection to server...");
#endif
      // if you get a connection, report back via serial:
      if (WebSocketClient.connect(command, 80)) {
#ifdef DEBUG
        SocketClient.println("connected to server");
#endif
        // Make a HTTP request:
        WebSocketClient.println("GET /comando.txt HTTP/1.1");
        WebSocketClient.println("Host: www.javisfryingchips.com");
        WebSocketClient.println("Connection: close");
        WebSocketClient.println();
        requestInProgress = true;
        LocalTimeout = millis();
      }
#ifdef DEBUG
      else
      {
        SocketClient.println("\nFail!");
      }
#endif
    }
  }

  if (requestInProgress)
  {
    if ( millis() - LocalTimeout < 10000)
    {
      if (WebSocketClient.available() ) {
        char c = WebSocketClient.read();
#ifdef DEBUG
        SocketClient.write(c);
#endif
        httpCommand += c;

        if (httpCommandComplete)
        {
          ret = httpCommand;
          httpCommand = "";
          requestInProgress = false;
          httpCommandComplete = false;
#ifdef DEBUG
          SocketClient.println("disconnecting from server.");
#endif
          WebSocketClient.stop();
        }

        if (c == '\n')
        {
          if (httpCommand.length() == 2)
          {
            httpCommandComplete = true;
          }
          httpCommand = "";
        }
      }
    }
  }
  return ret;
}

void WebClientEnabled(void)
{
  pollingEnabled = true;
}

void WebClientDisabled(void)
{
  pollingEnabled = false;
}

