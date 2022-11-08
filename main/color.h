#define RAD2DEG (360 / (2 * PI))

typedef struct
{
    int R;
    int G;
    int B;
} RGB_;

typedef struct
{
    float H;
    float S;
    float V;
} HSV_;

// Funtions prototype
HSV_ RGB2HSV(RGB_ *);
RGB_ HSV2RGB(HSV_ *);

// Actual functions

/*
For the color conversion see here (https://www.had2know.org/technology/hsv-rgb-conversion-formula-calculator.html#:~:text=Converting%20RGB%20to%20HSV&text=H%20%3D%20360%20%2D%20cos%2D1,cosine%20is%20calculated%20in%20degrees.)

*/
HSV_ RGB2HSV(RGB_ *rgb)
{
    float H, S, V;
    float R = rgb->R, G = rgb->G, B = rgb->B;

    float M = max(max(R, G), B);
    float m = min(min(R, G), B);

    // Compute V
    V = M / 255;

    // Compute S
    S = (M == 0) ? 0 : 1 - m / M;

    // Compute H
    if (rgb->G >= rgb->B)
        H = acos((R - 0.5f * G - 0.5f * B) / sqrt(R * R + G * G + B * B - R * G - R * B - G * B)) * RAD2DEG;
    else
        H = 360 - acos((R - 0.5f * G - 0.5f * B) / sqrt(R * R + G * G + B * B - R * G - R * B - G * B)) * RAD2DEG;

    return {H, S, V};
}

float abs_(float x)
{
    return (x > 0) ? x : -x;
}

float mod(float a, int b)
{
    return a - floor(a / b) * b;
}

RGB_ HSV2RGB(HSV_ *hsv)
{
    int R, G, B;
    float H = hsv->H, S = hsv->S, V = hsv->V;

    float M = 255 * V;
    float m = M * (1 - S);
    float z = (M - m) * (1 - abs_(mod(H / 60, 2) - 1));

    if (H < 60)
    {
        R = M;
        G = z + m;
        B = m;
    }
    else if (H < 120)
    {
        G = M;
        R = z + m;
        B = m;
    }
    else if (H < 180)
    {
        G = M;
        B = z + m;
        R = m;
    }
    else if (H < 240)
    {
        B = M;
        G = z + m;
        R = m;
    }
    else if (H < 300)
    {
        B = M;
        R = z + m;
        G = m;
    }
    else
    {
        R = M;
        B = z + m;
        G = m;
    }

    return {R, G, B};
}
