# 433Mhz jam
Simple WiFi controlled 433Mhz radio jammer.  
The project allows creating a 433MHz jammer using an ESP32 or ESP8266 that acts as a WiFi access point and webserver, and an FS1000A which as the radio transmitter.  

### ⚠️ WARNING ⚠️
Jamming frequencies is most likely illegal in your country.  
Make sure you know exactly what you are doing, as it can interfere with the normal functioning of devices around you.   
It's suggested to avoid jamming outside a controlled and isolated environment. 

## Motivation
This device was created as a simple, reliable and cheap device to aid during security research activities involving radio frequencies.  
A big advantage of this device is the remote control feature, allowing the usage in more flexible scenarios.

## Getting started
### Materials & assembly
433 Mhz jam uses cheap, easy to find and widely documented components:
  - ESP32/ESP8266 developement board
  - FS1000A
  - 433 Mhz antenna
  - Dupont connectors
  - Power supply (powerbank/battery pack for remote usage)
 
To connect the devices simply follow the schematics:
<p align="center">
  <img src="https://user-images.githubusercontent.com/78535423/200618065-28e11512-7293-4231-9715-651191cd74a3.png" height="400" alt="433 Mhz jam schematics"/>
</p>
Pay attention, as depending on your FS1000A the pins layout might vary.

The antenna can be bought or built. If you plan on going DIY, I suggest following [this guide](https://github.com/0xless/433mhz_jam/blob/main/How-to-make-a-Air-Cooled-433MHz-antenna.pdf) (found on the internet, not mine). 

Pin 4 is the default pin used to pilot the radio transmitter, it's been tested on both ESP32 and ESP8266, it works, but feel free to change it.

### Software
Before installing the software, you need to setup the Arduino IDE and configure it to work with ESP32 and/or ESP8266 boards.  
You will also need to install [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) and [AsyncTCP](https://github.com/me-no-dev/AsyncTCP).

Now you can simply clone the repository, open the `.ino` file in the Arduino IDE and flash the target board.

Before flashing, make sure to change the default SSID and password.

## Usage
To use 433Mhz jam you need to power on the device and wait a few seconds for it to complete booting up.  
After a while a new WiFi network should be available, connect to it and using a browser visit `192.168.2.1` (default board IP).  

At this point a simple html page with a button should show up. Press the button to start jamming! And press again to stop.

NOTE: in some phones, to connect to an IP in the local network, you need to disconnect phone data.
