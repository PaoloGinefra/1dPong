#ifndef LED
#include "led.h"
#define LED
#endif

#ifndef GAME
#include "game.h"
#define GAME
#endif

#define OPEN_SAT 1
#define OPEN_VAL 0.3f
#define OPEN_HUE_SPEED 0.5f

#define LIFE_BLINK_WAIT 0.5f

#define WINNING_LED_WAIT 0.02f

#define L_COLOR                 \
    {                           \
        236, OPEN_SAT, OPEN_VAL \
    }

#define R_COLOR               \
    {                         \
        0, OPEN_SAT, OPEN_VAL \
    }

#define BALL_COLOR     \
    {                  \
        0, 0, OPEN_VAL \
    }

// Time tracker in seconds
float t = 0;
float deltaTime = 0;
float oldTime = 0;

// Function prototypes
void OpenAnimation();
void LifeDisplay();
void DisplayGame();
void rightHit(int);
void leftHit(int);

float OpenHue = 0;
// Actual functions
void OpenAnimation()
{
    HSV_ color = {OpenHue, OPEN_SAT, OPEN_VAL};
    setAllColorsHSV(&color);
    OpenHue += OPEN_HUE_SPEED;
    OpenHue = mod(OpenHue, 360);
}

void LifeDisplay()
{
    cleanColors();

    if (t < LIFE_BLINK_WAIT)
    {
        for (int i = 0; i < lifes.lifeR; i++)
            colors[2 * i] = R_COLOR;

        for (int i = 0; i < lifes.lifeL; i++)
            colors[NUMPIXELS - 2 * i - 1] = L_COLOR;
    }

    if (t >= 2 * LIFE_BLINK_WAIT)
        t = 0;
}

void DisplayGame()
{
    cleanColors();
    colors[0] = R_COLOR;
    colors[NUMPIXELS - 1] = L_COLOR;

    if (game.hit > 0)
        rightHit(game.ballPos);
    else if (game.hit < 0)
        leftHit(game.ballPos);

    game.hit = 0;

    colors[(int)floor(game.ballPos)] = BALL_COLOR;
}

void rightHit(int pos)
{
    HSV_ bright = R_COLOR;
    bright.V *= 2;

    for (int i = 0; i < pos; i++)
    {
        colors[i] = bright;
    }
}

void leftHit(int pos)
{
    HSV_ bright = L_COLOR;
    bright.V *= 2;

    for (int i = NUMPIXELS - 1; i > pos; i--)
    {
        colors[i] = bright;
    }
}

int winningCounter = 1;
void WinningAnimation()
{
    if (t >= WINNING_LED_WAIT && winningCounter < NUMPIXELS)
    {
        if (game.lHasWon)
            colors[NUMPIXELS - 1 - winningCounter] = L_COLOR;
        else
            colors[winningCounter] = R_COLOR;
        winningCounter++;
        t = 0;
    }
}