import controlP5.*;

import processing.net.*; 
Client myClient; 
String dataIn;
String textmostrado;

ControlP5 cp5;
Textfield InputField;
Textfield[] ip = new Textfield[4];
Textfield port;
Textarea myTextarea;
Textlabel ipServer;
Textlabel portServer;
Button connectButton, disconnectButton;
boolean myServerRunning = true;
String[] ipText = {"192", "168", "1", "115"};


void setup() { 
  size(800, 620); 
  PFont font = createFont("arial", 20);
  cp5 = new ControlP5(this);
  myTextarea = cp5.addTextarea("txt")
    .setPosition(20, 50)
    .setSize(760, 430)
    .setFont(createFont("arial", 14))
    .setLineHeight(14)
    .setColor(color(180))
    .setColorBackground(color(255, 100))
    .setColorForeground(color(255, 100));

  myTextarea.setText("Welcome to the Christmas tree chat"+'\n');

  InputField=cp5.addTextfield("input")
    .setPosition(20, 520)
    .setSize(760, 60)
    .setFont(font)
    //.setFocus(true)
    .setColor(color(230))
    ;

  for (int i=0; i<4; i++)
  {
    ip[i]=cp5.addTextfield("ip"+Integer.toString(4-i))
      .setPosition(100+i*40, 12)
      .setSize(30, 20)
      .setFont(createFont("arial", 11))
      //.setFocus(true)
      .setColor(color(50))
      .setColorBackground(color(200))
      .setColorCaptionLabel(color(0))
      .setColorForeground(color(0))
      .setColorActive(color(230))
      .setLabelVisible(false)
      .setText(ipText[i])
      ;
  }

  port=cp5.addTextfield("port0")
    .setPosition(350, 12)
    .setSize(50, 20)
    .setFont(createFont("arial", 11))
    //.setFocus(true)
    .setColor(color(50))
    .setColorBackground(color(200))
    .setColorCaptionLabel(color(0))
    .setColorForeground(color(0))
    .setColorActive(color(230))
    .setLabelVisible(false)
    .setText("10002")
    ;

  ipServer = cp5.addTextlabel("iplabel")
    .setText("Server IP:")
    .setPosition(10, 10)
    .setColorValue(0xffffff00)
    .setFont(createFont("Georgiabold", 16))
    ;

  portServer = cp5.addTextlabel("portlabel")
    .setText("Port:")
    .setPosition(300, 10)
    .setColorValue(0xffffff00)
    .setFont(createFont("Georgiabold", 16))
    ;

  connectButton = cp5.addButton("Connect")
    .setPosition(430, 10)
    .setSize(130, 35)
    .setColorBackground(color(200))
    .setColorCaptionLabel(color(0))
    .setColorForeground(color(255))
    .setColorActive(color(230))
    ;

  disconnectButton = cp5.addButton("Disconnect")
    .setPosition(600, 10)
    .setSize(130, 35)
    .setColorBackground(color(200))
    .setColorCaptionLabel(color(0))
    .setColorForeground(color(255))
    .setColorActive(color(230))
    ;
} 

void draw() {
  background(0);
}

public void clientEvent(Client someClient) {
  dataIn = myClient.readStringUntil('\n');
  if (dataIn != null) {
    myTextarea.setColorValue (color(244, 245, 143));
    myTextarea.setText(myTextarea.getText()+"Fancy Christmas tree: "+ dataIn);
    //println(dataIn);
  }
}

public void input(String theText) {
  // automatically receives results from controller input
  myClient.write(theText + '\n');
  myTextarea.setColorValue (color(91, 232, 134));
  myTextarea.setText(myTextarea.getText()+"User: "+ theText + '\n');
}

public void Disconnect(int theValue)
{
  //connectButton.unlock();
  myClient.stop();
  //InputField.lock();
  //disconnectButton.lock();
}

public void Connect(int theValue)
{
  String ipString ="";
  String ipfraction="";
  boolean connection=true;
  int Pport=0;


  for (int i=0; i<3; i++)
  {
    ipfraction = ip[i].getText();
    if ((Integer.parseInt(ipfraction) < 0) && (Integer.parseInt(ipfraction) > 255))
    {
      myTextarea.setColorValue (color(255, 0, 0));
      myTextarea.setText(myTextarea.getText()+"ERROR: The IP is not correct!\n" );
      connection = false;
      break;
    }
    ipString+=ipfraction+".";
  }
  if (connection)
  {
    ipfraction = ip[3].getText();
    if ((Integer.parseInt(ipfraction) < 0) && (Integer.parseInt(ipfraction) > 255))
    {
      myTextarea.setColorValue (color(255, 0, 0));
      myTextarea.setText(myTextarea.getText()+"ERROR: The IP is not correct!\n" );
      connection = false;
    }
    ipString+=ipfraction;
  }

  if (connection)
  {
    if (port.getText() != null)
      Pport = Integer.parseInt(port.getText());
    else
    {
      myTextarea.setColorValue(color(255, 0, 0));
      myTextarea.setText(myTextarea.getText()+"I need a good port!" + "\n");
      connection = false;
    }
  }

  if (connection)
  {
    myTextarea.setColorValue (color(28, 174, 216));
    myTextarea.setText(myTextarea.getText()+"Trying connectButton to ip: " + ipString +" and port: " + Integer.toString(Pport)+"\n");

    myClient = new Client(this, ipString, Pport);

    if (myClient==null)
    {
      myTextarea.setColorValue (color(255, 0, 0));
      myTextarea.setText(myTextarea.getText()+"ERROR: Can not connectButton to ip: " +ipString+ "through port: " + Integer.toString(Pport)+"\n" );
    } else
    {
      myTextarea.setColorValue (color(28, 174, 216));
      myTextarea.setText(myTextarea.getText()+"connected to: " + myClient.ip()+"\n");
      //InputField.unlock();
      //disconnectButton.unlock();
      //connectButton.lock();
    }
  }
}