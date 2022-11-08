#ifndef INP
#include "input.h"
#define INP
#endif

#ifndef LED
#include "led.h"
#define LED
#endif

void (*state)();

// Function prototypes
void Open();
void Life();
void Game();
void Winner();

// Proper Functions
void Open()
{
    Serial.println("State = Open");

    ledLoop();

    // Transition to Life state when both buttons are pressed
    if (b1.isDown && b2.isDown)
        state = Life;
}

void Life()
{
    Serial.println("State = Life");
    delay(1000);

    state = Game;
}

void Game()
{
    Serial.println("State = Game");

    // Game loop
}