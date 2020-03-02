#include <avr/interrupt.h>
#include <avr/sleep.h>

/*
  Spot Welder with Sensor
  Detect button/pin interrupt, generate fixed length pulse, add mandatory time-out
  First version created 20191128 Matteljay
*/

const int WELD_PULSE_INTRO = 1000;
const int WELD_PULSE1 = 60;
const int WELD_PULSE_WAIT = 0;
const int WELD_PULSE2 = 0;
const int WELD_BUTTON_TIMEOUT = 1000;
const int WELD_PULSE_LONG_DEBUG = 15000;

const int PIN_LED = 4;
const int PIN_DRIVERS = 0;
const int PIN_SENSOR = 3;
const int PIN_PUSHBTN = 2;
const int PIN_PUSHBTN_INTERRUPT = 0;
void ret() {}

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_DRIVERS, OUTPUT);
  pinMode(PIN_SENSOR, INPUT);
  pinMode(PIN_PUSHBTN, INPUT_PULLUP);
}

void loop() {
  delay(200);
  /* sensor */
  if(digitalRead(PIN_SENSOR) == HIGH) {
    digitalWrite(PIN_LED, HIGH);
    delay(WELD_PULSE_INTRO);
    if(digitalRead(PIN_SENSOR) == LOW) {
      digitalWrite(PIN_LED, LOW);
      return;
    }
    digitalWrite(PIN_DRIVERS, HIGH);
    delay(WELD_PULSE1);
    digitalWrite(PIN_DRIVERS, LOW);
    digitalWrite(PIN_LED, LOW);
      do {
        delay(WELD_BUTTON_TIMEOUT);
      } while(digitalRead(PIN_SENSOR) == HIGH);
  }
  /* test-button */
  if(digitalRead(PIN_PUSHBTN) == LOW) {
    digitalWrite(PIN_LED, HIGH);
    digitalWrite(PIN_DRIVERS, HIGH);
    delay(WELD_PULSE_LONG_DEBUG);
    digitalWrite(PIN_DRIVERS, LOW);
    digitalWrite(PIN_LED, LOW);
  }
}

/* Double pulse experiments
void loop() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  attachInterrupt(PIN_PUSHBTN_INTERRUPT, ret, LOW);
  sleep_mode(); //blocking call
  sleep_disable();
  detachInterrupt(PIN_PUSHBTN_INTERRUPT);

  if(WELD_PULSE1 > 0) {
    digitalWrite(PIN_LED, HIGH);
    digitalWrite(PIN_DRIVERS, HIGH);
    delay(WELD_PULSE1);
    digitalWrite(PIN_DRIVERS, LOW);
    digitalWrite(PIN_LED, LOW);
  }

  if(WELD_PULSE_WAIT > 0) {
    delay(WELD_PULSE_WAIT);
  }

  if(WELD_PULSE2 > 0) {
    digitalWrite(PIN_LED, HIGH);
    digitalWrite(PIN_DRIVERS, HIGH);
    delay(WELD_PULSE2);
    digitalWrite(PIN_DRIVERS, LOW);
    digitalWrite(PIN_LED, LOW);
  }

  while(digitalRead(PIN_PUSHBTN) == LOW) {
    delay(WELD_BUTTON_TIMEOUT);
  }
}
*/

// EOF
