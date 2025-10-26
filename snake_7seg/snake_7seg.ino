#include <Arduino.h>

// PushButton class
class PushButton
{
    int pin;
    bool state;

public:
    PushButton(int p) : pin(p), state(HIGH)
    {
        pinMode(pin, INPUT);
    }

    bool justPressed()
    {
        bool newState = digitalRead(pin);
        if (newState == LOW && state == HIGH)
        {
            state = newState;
            return true;
        }
        state = newState;
        return false;
    }
};

// Buttons
PushButton buttonLeft(3);
PushButton buttonRight(2);

// 7-segment display pins: a-g
int displayPins[] = {6, 7, 5, 10, 11, 9, 8};

int loop1[] = {0, 1, 2, 3, 4, 5};
int loop2[] = {0, 1, 6, 5};
int loop3[] = {2, 3, 4, 6};

int *loops[] = {loop1, loop2, loop3}; // array of pointers
int loop_lengths[] = {6, 4, 4};       // lengths of each array

int pos = 0; // current segment

int loopPos = 0;
int loopIdx = 1;
int dir = 1; // 1 - CW, -1 - CCW

void setup()
{
    for (int i = 0; i < 7; i++)
        pinMode(displayPins[i], OUTPUT);

    pos = loops[loopIdx][loopPos];
    digitalWrite(displayPins[pos], HIGH);
    Serial.begin(9600);
}

void switchLoops()
{
    // Outer loop -> inner loops via intersections
    if (loopIdx == 0)
    {
        if ((dir == 1) && (loopPos == 1))
        {
            loopIdx = 1;
            loopPos = 1;
        }
        else if ((dir == -1) && (loopPos == 4))
        {
            loopIdx = 2;
            loopPos = 2;
        }
    }
    else if (loopIdx == 1)
    {
        if ((dir == 1) && (loopPos == 2))
        {
            loopIdx = 2;
            dir *= -1;
            loopPos = 3;
        }
    }
    else if (loopIdx == 2)
    {
        if ((dir == -1) && (loopPos == 1))
        {
            loopIdx = 1;
            dir *= -1;
            loopPos = 2;
        }
    }
}

void loop()
{
    // Move along current loop
    digitalWrite(displayPins[pos], LOW);
    loopPos = (loopPos + dir + loop_lengths[loopIdx]) % loop_lengths[loopIdx];
    pos = loops[loopIdx][loopPos];
    digitalWrite(displayPins[pos], HIGH);

    // Player can switch loops at intersections
    if (buttonLeft.justPressed())
        switchLoops();

    Serial.print(buttonLeft.justPressed());
    Serial.print("Pos: ");
    Serial.print(pos);
    Serial.print("  LoopPos: ");
    Serial.print(loopPos);
    Serial.print("  LoopIdx: ");
    Serial.println(loopIdx);

    delay(500); // snake speed
}
