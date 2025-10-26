#include <Arduino.h>

int displayPins[] = {4, 5, 6, 7, 8, 9, 10, 11};
int buttonPin = 3;

int idx = 0;
bool lastButtonState = LOW;

void setup()
{
    for (int pin : displayPins)
    {
        pinMode(pin, OUTPUT);
    }

    pinMode(buttonPin, INPUT);
}

void loop()
{

    bool buttonState = digitalRead(buttonPin);

    if (buttonState == LOW && lastButtonState == HIGH)
    {
        digitalWrite(displayPins[idx], LOW);
        idx = (idx + 1) % 8;
        digitalWrite(displayPins[idx], HIGH);
        delay(50); // basic debounce
    }

    lastButtonState = buttonState;
}