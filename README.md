# Arduino-PowerOutageDetector

Simple Arduino project to detect power outages. Following the KISS principle, the Arduino is limited to:

- Detect changes on power supply status
- Notify status using Serial
- Turn ON/OFF two ON/OFF status LEDs

![Schematic](ArduinoPowerOutageDetector_Schematic.png)

## Requirements

- Arduino, any basic model is enough, but Serial is required (internal Serial<->USB converter recommended). Built on Arduino Nano compatible board with ATMega168P MCU.
- PC817C Optocoupler.
- 5V AC-DC adapter.
- A device to read the Serial output of the Arduino and perform the required actions on power ON or OFF (e.g. send a message to a MQTT topic, turn ON/OFF a computer...).
- (optional) 1x or 2x LED, 1 switch

## How does it work?

The Arduino should be connected through USB to a computer or low power device (e.g. a router, a RPi) that can read the Serial output from the Arduino.
This computer/device is supposed to be connected to a UPS or battery, so when there is a power outage, the Arduino and device can know that it happened and do whatever is supposed to do.

Outside of the UPS, a 5V AC-DC adapter feeds the Optocoupler (so the Arduino -UPS powered- circuit is isolated from the output circuit).

When there is a power outage (a.k.a. the 5V AC-DC adapter is OFF) the optocoupler turns off, so the Control Pin of the Arduino detects this change on the power status.

## Pinout

- Control Pin (2): optocoupler 5V output (HIGH when power is ON, LOW when power is OFF)
- ON LED (3): optional LED, turns ON when the power is ON, turns OFF when the power is OFF
- OFF LED (4): optional LED, turns ON when the power is OFF, turns OFF when the power is ON
- Maintenance Mode Switch: optional switch that can be activated to disable the power outage detection when the 5V adapter will be disconnected temporary due to some maintenance.

## Versions

- PowerOutageDetector_Simple: Simple/classic Arduino version with a constantly running loop
- PowerOutageDetector_Interrupt_Sleep: version that uses LowPower library to turn OFF the Arduino after detecting a change on the power status and sending it through Serial, using External Pin Interrupts. The Arduino will wake up after detecting another change.
