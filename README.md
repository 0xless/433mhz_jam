# 433Mhz jam

Simple WiFi controlled 433Mhz radio jammer.
The device is composed of an ESP32 that acts as a WiFi access point and webserver, and an FS1000A which is the radio transmitter.

## Motivation
This device was create as a simple, reliable and cheap device to aid during security research activities involving radio frequencies.
A big advantage of this device is the remote control feature, allowing the usage in more flexible scenarios.

## Getting started

### Materials & assembly
433 Mhz jam uses cheap, easy to find and widely documented components:
  - ESP32 developement board
  - FS1000A (AKA cheap FM transmitter)
  - DIY 433 Mhz antenna
  - Dupont connectors
  - Power supply (powerbank/battery pack for remote usage)
 
To connect the devices simply follow the schematics:
<p align="center">
  <img src="https://user-images.githubusercontent.com/78535423/200618065-28e11512-7293-4231-9715-651191cd74a3.png" height="400" alt="433 Mhz jam schematics"/>
</p>

NOTE: depending on your ESP32 board, using some pins as data pin can cause a bootloop! 
Pin 4 should be safe, but if you plan on changing it, make sure to check for bootloops.

### Software
