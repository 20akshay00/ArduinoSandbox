#include <Arduino.h>

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT); // Initialize the built-in LED pin
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on
    delay(100);                      // Wait 500 milliseconds
    digitalWrite(LED_BUILTIN, LOW);  // Turn the LED off
    delay(100);                      // Wait 500 milliseconds
}
