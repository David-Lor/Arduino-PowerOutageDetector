/*  ARDUINO POWER OUTAGE DETECTOR
 *  
 *  - Detect power outage on the main power line using an external DC input and an optocoupler.
 *  - Notify through Serial.
 *  - Turn ON/OFF two leds depending on power status.
 */

//Pinout & loop
#define PIN_INPUT 2
#define PIN_LED_ON 3
#define PIN_LED_OFF 4
#define LOOP_DELAY 100

//Serial settings & messages
#define SERIAL_SPEED 9600
#define SERIAL_MSG_STARTUP "PowerOutageDetector:ONLINE"
#define SERIAL_MSG_STATUS_ON "Power:ON"
#define SERIAL_MSG_STATUS_OFF "Power:OFF"

//Global variables
byte powerStatus = 255;

////////////////////////////////////////////////

void setLED() {
  digitalWrite(PIN_LED_ON, powerStatus);
  digitalWrite(PIN_LED_OFF, !powerStatus);
}

bool readStatus() {
  return digitalRead(PIN_INPUT);
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
  bool currentStatus = readStatus();
  
  if (currentStatus != powerStatus) {
    powerStatus = currentStatus;
    setLED();
    sendStatus();
  }

  delay(LOOP_DELAY);
}
