#include "DigiKeyboard.h"

#define KEY_COMMAND (1<<3)
#define KEY_OPTION (1<<2)
#define KEY_CONTROL (1<<0)

#define KEY_POWER 0x66
#define KEY_EJECT 0xb8

#define MIN_VOLTAGE 80
#define MAX_VOLTAGE 100

int loopCount = 0;

void setup() {
    pinMode(2, INPUT);
}

void loop() {
  DigiKeyboard.delay(200);
  while (analogRead(1) >= MIN_VOLTAGE) {
    // count loops while button is pressed
    loopCount++;
    delay(100);
  }

  // Control + Power button || Control + Media Eject: shut down with confirm
  // Control + Option + Command + Power button || Control + Option + Command + 
  // Media Eject: shut down your Mac without confirm
  // sendKeyPress(0) to release current pressed keys

  // time of button pressed is loopCount * 100ms
  if (loopCount > 2 && loopCount < 13) {
    // if time > 100ms and < 1.3s send keyboard shortcut for activate sleep
    DigiKeyboard.sendKeyStroke(0);
    DigiKeyboard.sendKeyStroke(KEY_POWER, KEY_COMMAND | KEY_OPTION);
    DigiKeyboard.delay(250);
  }
  else if (loopCount > 12) {
    // if time >= 1.3s send keyboard shortcut to pop up shutdown dialog
    DigiKeyboard.sendKeyStroke(0);
    DigiKeyboard.sendKeyStroke(KEY_POWER, KEY_CONTROL);
    DigiKeyboard.delay(250);
  }
  // reset loop count, if button not pressed or released
  loopCount = 0;
}
