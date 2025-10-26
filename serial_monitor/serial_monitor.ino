#include <Arduino.h>

void setup()
{
    Serial.begin(9600); // Start serial communication at 9600 baud
}

void loop()
{
    Serial.println("Hello World"); // Print with newline
    delay(100);                    // Wait 1 second
}
