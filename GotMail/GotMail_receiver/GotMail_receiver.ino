/*-----------------------------------------
 "GotMail_receiver.ino"
 ver 21 - 2016-12-14

  GotMail Reciver code
  by
  frykberg
-----------------------------------------*/
#include <VirtualWire.h>
#include "FastLED.h"

const byte numPixelLeds = 24;
const byte statusLedPin = 13;
const byte pixelLedPin =  3;
const byte receivePin =   12;
const byte buttonPin =    2;

CRGB leds[numPixelLeds];
bool mailReceived = false;

void setup() {
  
  delay(1000);
  FastLED.addLeds<WS2812, pixelLedPin, GRB>(leds, numPixelLeds);
  FastLED.clear();
  vw_set_rx_pin(receivePin);
  vw_setup(2000);
  vw_rx_start();
  pinMode(statusLedPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPress, FALLING);
  
}

void loop() {

  uint8_t rxBuf[VW_MAX_MESSAGE_LEN];
  uint8_t rxBuflen = VW_MAX_MESSAGE_LEN;

  while (mailReceived == false) {
    if (vw_get_message(rxBuf, &rxBuflen) == true) {
      digitalWrite (statusLedPin, HIGH);
      mailReceived = true;
      digitalWrite (statusLedPin, LOW);
    }
  }

  if (mailReceived == true) {
    for (int i = 0; i < numPixelLeds; i++) {
      leds[i] = CHSV( 10.625 * i, 200, 10);
      FastLED.show();
      leds[i] = CHSV( 10.625 * i, 200, 100);
      delay(30);
    }
    for (int j = 100; j < 255; j++) {
      for (int i = 0; i < numPixelLeds; i++) {
        leds[i] = CHSV( 10.625 * (i - j), 200, j);
      }
      FastLED.show();
      delay(24);
    }
    for (int j = 255; j > 100; j--) {
      for (int i = 0; i < numPixelLeds; i++) {
        leds[i] = CHSV( 10.625 * (i + j), 200, j);
      }
      FastLED.show();
      delay(24);
    }
    while (mailReceived == true) {
      for (int i = 0; i < numPixelLeds; i++) {
        leds[i] = CHSV( 10.625 * i, 200, 10);
        FastLED.show();
        leds[i] = CHSV( 10.625 * i, 200, 100);
        delay(30);
      }
    }
  }
  if (mailReceived == false) {
    for (int i = 0; i < numPixelLeds; i++) {
      leds[i] = CHSV( 10.625 * i, 200, 100);
      FastLED.show();
      leds[i] = CRGB::Black;
      delay(30);
    }
    FastLED.clear();
    FastLED.show();
  }
}

void buttonPress() {
  mailReceived = !mailReceived;
}

