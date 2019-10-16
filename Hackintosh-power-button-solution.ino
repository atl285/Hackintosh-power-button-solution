#include "DigiKeyboard.h"

#define KEY_COMMAND (1<<3)
#define KEY_OPTION (1<<2)
#define KEY_CONTROL (1<<0)
#define KEY_POWER 0x66
#define KEY_EJECT 0xb8

void setup() {
    pinMode(2, INPUT);
}

void loop() {
    DigiKeyboard.delay(100);
    int anaValue = analogRead(1);
    if (anaValue >= 760 && anaValue < 770) {
        // Control + Power button || Control + Media Eject: shut down with confirm
        // Control + Option + Command + Power button || Control + Option + Command + 
        // Media Eject: shut down your Mac without confirm
        // sendKeyPress(0) to release current pressed keys
        DigiKeyboard.sendKeyPress(0);
        DigiKeyboard.sendKeyPress(KEY_POWER, KEY_CONTROL | KEY_OPTION | KEY_COMMAND);
        DigiKeyboard.delay(3000);
    }
}