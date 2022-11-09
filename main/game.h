#ifndef LED
#include "led.h"
#define LED
#endif

#ifndef INP
#include "input.h"
#define INP
#endif

#define MAX_LIFE 3
#define PAD_LENGTH 3

typedef struct
{
    int lifeL = MAX_LIFE;
    int lifeR = MAX_LIFE;
} Lifes_;

typedef struct
{
    float ballPos = NUMPIXELS / 2;
    float ballSpeed = 50;
    float ballAcc = 0.1f;
    bool lostLife = false;
    int hit = 0;
    bool winner = false;
    bool lHasWon = false;
} Game_;

Lifes_ lifes;
Game_ game;

// returns wheather a life has been lost
void gameStep(Game_ *game, float deltaTime)
{
    if (game->ballPos < PAD_LENGTH && b2.isPressed || game->ballPos > NUMPIXELS - PAD_LENGTH - 1 && b1.isPressed)
    {
        game->ballSpeed *= -1;
        game->hit = (b2.isPressed) ? 1 : -1;
    }

    game->ballSpeed += game->ballAcc * deltaTime;
    game->ballPos += game->ballSpeed * deltaTime;

    if (game->ballPos > NUMPIXELS - 1)
    {
        lifes.lifeL--;
        game->lostLife = true;
    }
    if (game->ballPos < 0)
    {
        lifes.lifeR--;
        game->lostLife = true;
    }

    game->winner = lifes.lifeR <= 0 || lifes.lifeL <= 0;
    game->lHasWon = lifes.lifeR <= 0;
}

void resetGame(Game_ *game)
{
    game->ballPos = NUMPIXELS / 2;
    game->ballSpeed *= -1;
    game->lostLife = false;
}

void restartGame()
{
    lifes.lifeL = MAX_LIFE;
    lifes.lifeR = MAX_LIFE;
}