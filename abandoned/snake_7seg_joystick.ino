#include <Arduino.h>

short getAxisValue(int pin)
{
    return map(analogRead(pin), 0, 1023, 0, 255) - 128;
}

class AnalogJoystick
{
private:
    int x, y;
    int xPin, yPin, buttonPin;
    bool isPressed;

public:
    AnalogJoystick(int xPin, int yPin, int buttonPin)
        : xPin(xPin), yPin(yPin), buttonPin(buttonPin), x(0), y(0), isPressed(false) {}

    void setup()
    {
        pinMode(buttonPin, INPUT_PULLUP);
    }

    void poll()
    {
        x = getAxisValue(xPin);
        y = getAxisValue(yPin);

        // deadzone
        if ((abs(x) < 64) && (abs(y) < 64))
        {
            x = 0;
            y = 0;
        }

        isPressed = digitalRead(buttonPin) == 0;
    }

    short getX() const { return x; }
    short getY() const { return y; }
    bool isButtonPressed() const { return isPressed; }
};

int displayPins[] = {6, 7, 5, 10, 11, 9, 8};
int idx = 0;
int dir = 0;

AnalogJoystick joystick(A0, A1, A2);

const int grid[7][4] = {
    {f, b, -1, -1}, // a: LEFT, RIGHT, DOWN, UP
    {},             // b
    {6, -1, 3, 1},  // c
    {4, 2, -1, 6},  // d
    {-1, 3, -1, 5}, // e
    {-1, 0, 4, -1}, // f
    {5, 1, 3, 0}    // g
};

void setup()
{
    for (int pin : displayPins)
    {
        pinMode(pin, OUTPUT);
    }

    joystick.setup();

    idx = 1;
    digitalWrite(displayPins[idx], HIGH);

    Serial.begin(9600);
}

void loop()
{
    joystick.poll();
    int x = joystick.getX();
    int y = joystick.getY();

    if (abs(x) > abs(y))
    {
        if (x > 0)
            dir = 1; // RIGHT
        else if (x < 0)
            dir = 3; // LEFT
    }
    else
    {
        if (y > 0)
            dir = dir; // DOWN
        else if (y < 0)
            dir = 2; // UP
    }

    int new_idx = grid[idx][dir];
    if (new_idx != -1)
    {
        digitalWrite(displayPins[idx], LOW);
        idx = new_idx;
        digitalWrite(displayPins[idx], HIGH);
    }

    delay(500);
    Serial.println("(" + String(joystick.getX()) + ", " + String(joystick.getY()) + ")");
    Serial.println(idx);
}