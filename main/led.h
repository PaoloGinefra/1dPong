#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#include "color.h"

#define PIXELS_PIN 7
#define NUMPIXELS 38

#define SAT 1
#define VAL 0.1f

HSV_ colors[NUMPIXELS];

Adafruit_NeoPixel pixels(NUMPIXELS, PIXELS_PIN, NEO_GRB + NEO_KHZ800);

// Function prototypes
void ledSetup();
void setPixel(int, RGB_ *);
void setPixelHSV(int, HSV_ *);
void displayColors();

void cleanColors();

void setAllColorsHSV(HSV_ *);

// Actual functions
/*
This fuction needs to be called in the main setup
*/

void ledSetup()
{
    pixels.begin();
    cleanColors();
    displayColors();
}

void ledLoop()
{
    displayColors();
}

void cleanColors()
{
    for (int i = 0; i < NUMPIXELS; i++)
    {
        colors[i] = {0, 0, 0};
    }
}

void displayColors()
{
    for (int i = 0; i < NUMPIXELS; i++)
    {
        setPixelHSV(i, &(colors[i]));
    }
    pixels.show();
}

void setPixel(int i, RGB_ *c)
{
    pixels.setPixelColor(i, pixels.Color(c->R, c->G, c->B));
}

void setPixelHSV(int i, HSV_ *c_)
{
    RGB_ c = HSV2RGB(c_);
    setPixel(i, &c);
}

void setAllColorsHSV(HSV_ *col)
{
    for (int i = 0; i < NUMPIXELS; i++)
    {
        colors[i] = *col;
    }
}