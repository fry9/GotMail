/*-----------------------------------------
 "GotMail_transmitter.ino"
 ver 21 - 2016-12-14

  GotMail Transmitter code
  by
  frykberg
-----------------------------------------*/
#include <VirtualWire.h>

const byte statusLedPin = 13;
const byte transmitPin =  11;

void setup() {

  pinMode(statusLedPin, OUTPUT);
  vw_set_tx_pin(transmitPin);
  vw_setup(2000);

}

void loop() {

  char message[3] = {'1', '1', '1'};
  digitalWrite(statusLedPin, HIGH);
  vw_send((uint8_t *)message, 3);
  vw_wait_tx();
  digitalWrite(statusLedPin, LOW);
  delay(100);

}

