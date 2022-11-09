#define B1_PIN 3
#define B2_PIN 4

typedef struct
{
    int Pin;
    bool isDown;
    bool isPressed;
    bool isReleased;
    bool oldVal;
    bool toggle;
} Button_;

Button_ b1 = {B1_PIN};
Button_ b2 = {B2_PIN};

void inputSetup();
void inputLoop();
void updateButton(Button_ *);

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

void unToggleButton(Button_ *b)
{
    b->toggle = false;
}
