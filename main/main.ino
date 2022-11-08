#ifndef LED
#include "led.h"
#define LED
#endif

#include "stateMachine.h"

#ifndef INP
#include "input.h"
#define INP
#endif

void setup()
{
    Serial.begin(9600);

    inputSetup();
    ledSetup();

    state = Open;
}

void loop()
{
    inputLoop();
    state();
}