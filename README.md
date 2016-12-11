# ChristmasTreeIoT
Christmas Tree lights controlled by an Arduino MKR1000 board

## How to connect your low cost Christmas lights to internet ##

Don't be afraid, take your Christmas lights and open the small box. You will see something like this:

![](https://raw.githubusercontent.com/javifercep/ChristmasTreeIoT/master/doc/ChristmasLightsComponentsI.jpg)

![](https://raw.githubusercontent.com/javifercep/ChristmasTreeIoT/master/doc/ChristmasLightsComponentsII.jpg)


The electronics inside are something similar to this:

![](http://i02.c.aliimg.com/blog/upload/2010/07/01/01/55d8d5fa21b6424481a4889db7bcade6)

With basic electronics knowledge is easy to follow the PCB connections. I have seen there are different implementations for the same "circuit concept", so I recommend to take look to it.

The idea is simple: replacing the integrated controller from the lights by an Arduino MKR1000 board so the lights will be connected to internet.

First of all, remove the integrated YD803-2 controller (it looks like it is very used for this kind of things)

![](https://raw.githubusercontent.com/javifercep/ChristmasTreeIoT/master/doc/YD803-2.jpg)

This chip is inserting PWM into the two/four transistors that allows to drive the LEDs. So we just need to connect the Arduino MKR1000 PWM into this pins. In the picture above, the blue wire is GND and the two red wires are connected to the gates of the transistors:

![](https://raw.githubusercontent.com/javifercep/ChristmasTreeIoT/master/doc/Rework.jpg)

Then connect this signals to the MKR1000 board.

![](https://raw.githubusercontent.com/javifercep/ChristmasTreeIoT/master/doc/MKR1000Connection.jpg)

Unfortunately, I'm not sure how is the right way to use the circuit to provide power to the MKR1000 directly from the Christmas lights circuit, so I've preferred to power the Arduino using an old mobile phone charger.

This is the result of the experiment:

![](https://raw.githubusercontent.com/javifercep/ChristmasTreeIoT/master/doc/Final.jpg)

## Commands ##

The commands supported by the MKR1000 are very simple:

- **"a\n":** Increases the frequency of the blink led (for testing purpose)
- **"b\n":** Decreases the frequency of the blink led (for testing purpose)
- **"c\n":** Turn off the lights
- **"d\n":** Turn on the lights
- **"e\n":** Lights sequence 1
- **"f\n":** Lights sequence 2
- **"g\n":** Lights sequence 3
- **"h\n":** Lights sequence 4
- **"i\n":** Lights sequence 5

This commands are received from a socket, so any device in the network (or configuring the network properly for external devices) is able to send this commands.

Inside the ChristmasTreeChat folder there is a "client" chat developed in processing that you can use to send these commands or develop new ones.

On the other hand, I have found a nice Android application called "Socket Control Widget" that allows you to create a button like a widget with an integrated socket command that works perfectly. For example, for turning on the lights, once the widget is created appears a configuration window where the button name is specified and the command must be something like this:

    Ip:port/command -> Example: 192.168.1.3:30005/d\n

