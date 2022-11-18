/*
========================================================================
This files handles the buttons.

Every button has its own struct that records its state and a bunch
of other useful information.

There are three functions. An input Setup and Loop that need to be called
 in the Setup and Loop of the main file repectively
========================================================================
*/

#define B1_PIN 3
#define B2_PIN 4

typedef struct
{
    int Pin;

    // True when the button is held down
    bool isDown;

    // True only when the button is pressed
    bool isPressed;

    // True only when the button is released
    bool isReleased;

    // The value of the button on the previous iteration
    bool oldVal;

    // Records if the button has been pressed
    bool toggle;
} Button_;

// initialize buttons
Button_ b1 = {B1_PIN};
Button_ b2 = {B2_PIN};

// Funtions prototype
void inputSetup();
void inputLoop();
void updateButton(Button_ *);

// Actual Functions
void inputSetup()
{
    pinMode(b1.Pin, INPUT);
    pinMode(b2.Pin, INPUT);

    b1.oldVal = 0;
    b2.oldVal = 0;
}

void inputLoop()
{
    updateButton(&b1);
    updateButton(&b2);
}

void updateButton(Button_ *b)
{
    b->isDown = digitalRead(b->Pin);
    bool changed = b->isDown != b->oldVal;
    b->isPressed = b->isDown && changed;
    b->isReleased = !(b->isDown) && changed;
    b->oldVal = b->isDown;
    b->toggle |= b->isPressed;
}

// This resets the toggle property
void unToggleButton(Button_ *b)
{
    b->toggle = false;
}
