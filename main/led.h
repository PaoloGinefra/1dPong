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
void updateColors();

// Actual functions
/*
This fuction needs to be called in the main setup
*/

float hue = 0;
void ledSetup()
{
    pixels.begin();

    for (int i = 0; i < NUMPIXELS; i++)
    {
        colors[i] = {hue, SAT, VAL};
        pixels.setPixelColor(i, pixels.Color(0, 255, 255));
    }

    pixels.show();
}

void ledLoop()
{
    updateColors();
    displayColors();
    hue += 1;
    hue = mod(hue, 360);
}

void displayColors()
{
    for (int i = 0; i < NUMPIXELS; i++)
    {
        setPixelHSV(i, &(colors[i]));
    }
    pixels.show();
}

void updateColors()
{
    for (int i = 0; i < NUMPIXELS; i++)
    {
        colors[i] = {hue, SAT, VAL};
    }
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