/*  ARDUINO POWER OUTAGE DETECTOR
 *  
 *  - Detect power outage on the main power line using an external DC input and an optocoupler.
 *  - Detect changes on power status using interrumptions.
 *  - Sleep Arduino and wake up using the interrumption.
 *  - Notify through Serial.
 *  - Turn ON/OFF two leds depending on power status.
 */
#include "LowPower.h"

//Pinout & loop
//Input must be 2/3 to use interruptions
#define PIN_INPUT 2
#define PIN_LED_ON 3
#define PIN_LED_OFF 4

//Serial settings & messages
#define SERIAL_SPEED 9600
#define SERIAL_MSG_STARTUP "PowerOutageDetector:ONLINE"
#define SERIAL_MSG_STATUS_ON "Power:ON"
#define SERIAL_MSG_STATUS_OFF "Power:OFF"

//Global variables
bool powerStatus;

////////////////////////////////////////////////

void setLED() {
  digitalWrite(PIN_LED_ON, powerStatus);
  digitalWrite(PIN_LED_OFF, !powerStatus);
}

bool readStatus() {
  powerStatus = digitalRead(PIN_INPUT);
}

void sendStatus() {
  if (powerStatus) {
    Serial.println(F(SERIAL_MSG_STATUS_ON));
  } else {
    Serial.println(F(SERIAL_MSG_STATUS_OFF));
  }
}

////////////////////////////////////////////////

void setup() {
  Serial.begin(SERIAL_SPEED);
  pinMode(PIN_INPUT, INPUT);
  pinMode(PIN_LED_ON, OUTPUT);
  pinMode(PIN_LED_OFF, OUTPUT);
  Serial.println(F(SERIAL_MSG_STARTUP));

  //Disable peripherals
  ADCSRA = ADCSRA & B01111111;
  ACSR = B10000000;
  DIDR0 = DIDR0 | B00111111;
}

void loop() {
  readStatus();
  setLED();
  sendStatus();

  attachInterrupt(0, readStatus, CHANGE);
  Serial.flush();
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  detachInterrupt(0);
}
