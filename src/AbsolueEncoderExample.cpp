/*
Relative/Absolute Encoder Library using Arduino Framework
Developed for the University of Ottawa Rover Team (UORover)

UORover Encoder Library © 2023 by Majd Aburas is licensed under
Attribution 4.0 International.
To view a copy of this license, visit http://creativecommons.org/licenses/by/4.0/
*/

#include <Arduino.h>
#include "Encoder.h"

Encoder encoder(3, 4, 5, 6, Encoder::Absolute);

void encoderISR() {
    encoder.readQuadrature();
}

void setup() {
    encoder.setPositionConversionFactor(360); // Convert Encoder Rotations to Degrees
    encoder.setVelocityConversionFactor(60); // Convert Encoder Rotations per second to RPM
    attachInterrupt(digitalPinToInterrupt(3), encoderISR, CHANGE);
    Serial.begin(9600);
}

void loop() {
    encoder.update();
    Serial.print("Position: ");
    Serial.print(encoder.getPosition());
    Serial.print(" | Velocity: ");
    Serial.println(encoder.getVelocity());
}