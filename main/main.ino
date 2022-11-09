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
    randomSeed(analogRead(0));

    inputSetup();
    ledSetup();

    state = Open;
}

void loop()
{
    inputLoop();

    state();

    ledLoop();

    deltaTime = millis() / 1000.0f - oldTime;
    t += deltaTime;
    oldTime = millis() / 1000.0f;
}