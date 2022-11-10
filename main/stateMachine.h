#ifndef INP
#include "input.h"
#define INP
#endif

#ifndef LED
#include "led.h"
#define LED
#endif

#ifndef ANIM
#include "animations.h"
#define ANIM
#endif

#ifndef GAME
#include "game.h"
#define GAME
#endif

void (*state)();

// Function prototypes
void transitionTo(void (*target)());

void Open();
void Life();
void Game();
void Winner();

// Proper Functions
void transitionTo(void (*target)())
{
    unToggleButton(&b1);
    unToggleButton(&b2);
    t = 0;
    state = target;
}

void Open()
{
    OpenAnimation();

    // Transition to Life state when both buttons are pressed
    if (b1.toggle && b2.toggle)
        transitionTo(Life);
}

void Life()
{
    LifeDisplay();

    // Transition to Game state when both buttons are pressed
    if (b1.toggle && b2.toggle)
        transitionTo(Game);
}

void Game()
{
    // Game loop
    gameStep(&game, deltaTime, t);
    DisplayGame();

    // Transition to Life state when a life is lost
    if (game.lostLife)
    {
        resetGame(&game);
        if (game.winner)
        {
            restartGame();
            transitionTo(Winner);
        }
        else
        {
            game.lostLife = false;
            transitionTo(Life);
        }
    }
}

void Winner()
{
    WinningAnimation();
    if (b1.toggle && b2.toggle)
    {
        winningCounter = 1;
        OpenHue = colors[0].H;
        transitionTo(Open);
    }
}