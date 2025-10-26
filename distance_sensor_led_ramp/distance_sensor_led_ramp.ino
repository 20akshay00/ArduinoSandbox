#include <Arduino.h>

int ledPin = 3;
const int trigPin = 9;
const int echoPin = 10;

float duration, raw_distance, distance;
float max_distance = 15.;

float alpha = 0.4; // smoothing factor (0.1-0.3 typical)

void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(9600);
}

void loop()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    raw_distance = (duration * 0.0343) / 2;

    Serial.print("\nDistance: ");
    Serial.print(raw_distance);

    distance = alpha * raw_distance + (1 - alpha) * distance;

    if (distance < max_distance)
        analogWrite(ledPin, int((1 - distance / max_distance) * 255));
    else
        analogWrite(ledPin, 0);

    delay(100);
}
