/*
Relative/Absolute Encoder Library using Arduino Framework
Developed for the University of Ottawa Rover Team (UORover)

UORover Encoder Library © 2023 by Majd Aburas is licensed under
Attribution 4.0 International.
To view a copy of this license, visit http://creativecommons.org/licenses/by/4.0/
*/

#include "Encoder.h"

Encoder::Encoder(byte ABS) {
    // Constructor implementation
    this->A = -1;
    this->B = -1;
    this->Index = -1;
    this->ABS = ABS;
    this->inverted = false;
    this->zeroOffset = 0.0;
    this->position = 0.0;
    this->posFactor = 1.0;
    this->velocity = 0.0;
    this->velFactor = 1.0;
    this->prevTime = 0;
    this->prevPosition = 0;
    this->type = Absolute;
}

Encoder::Encoder(byte A, byte B) : Encoder(-1) {
    // Constructor implementation
    this->A = A;
    this->B = B;
    this->type = Quadrature;
}

Encoder::Encoder(byte A, byte B, byte Index) : Encoder(A, B) {
    // Constructor implementation
    this->Index = Index;
}

Encoder::Encoder(byte A, byte B, byte Index, byte ABS) : Encoder(A, B, Index) {
    // Constructor implementation
    this->ABS = ABS;
    this->type = Alternate;
}

Encoder::Encoder(byte A, byte B, byte Index, byte ABS, Encoder::Type type) : Encoder(A, B, Index, ABS) {
    // Constructor implementation
    this->type = type;
}

void Encoder::begin() const {
    pinMode(this->A, INPUT_PULLUP);
    pinMode(this->B, INPUT_PULLUP);
}

void Encoder::update() {
    // Retrieve Absolute Encoder Data from ABS pin over Duty Cycle
    if (this->type == Encoder::Type::Absolute || this->type == Encoder::Type::Alternate)
        this->position = float(pulseIn(this->ABS, HIGH) - 1) / 1023;
    else
        this->readQuadrature();

    // Get the current time
    unsigned long currentTime = millis();

    // Calculate the velocity using the change in position and time
    this->velocity = (this->position - this->prevPosition) / ((double(currentTime) - double(this->prevTime)) / 1000.0);

    // Save the current position and time for the next update
    this->prevPosition = this->position;
    this->prevTime = currentTime;
}

void Encoder::readQuadrature() {
    // Quadrature decoding logic
    this->position += (this->inverted ^ digitalRead(this->B)) ? 1 : -1;
}

void Encoder::setInverted(bool state) {
    // Implementation of setInverted
    this->inverted = state;
}

bool Encoder::getInverted() const {
    // Implementation of getInverted
    return this->inverted;
}

void Encoder::setZeroOffset(double offset) {
    // Implementation of setZeroOffset
    this->zeroOffset = offset;
}

double Encoder::getZeroOffset() const {
    // Implementation of getZeroOffset
    return this->zeroOffset;
}

void Encoder::setPositionConversionFactor(double factor) {
    // Implementation of setPositionConversionFactor
    this->posFactor = factor;
}

double Encoder::getPositionConversionFactor() const {
    // Implementation of getPositionConversionFactor
    return this->posFactor;
}

void Encoder::setVelocityConversionFactor(double factor) {
    // Implementation of setVelocityConversionFactor
    this->velFactor = factor;
}

double Encoder::getVelocityConversionFactor() const {
    // Implementation of getVelocityConversionFactor
    return this->velFactor;
}

void Encoder::setPosition(double newPosition) {
    // Implementation of setPosition
    this->position = newPosition / this->posFactor;
}

double Encoder::getPosition() const {
    // Implementation of getPosition
    // Return the current encoder position
    return this->position * this->posFactor;
}

double Encoder::getVelocity() const {
    // Implementation of getVelocity
    // Return the current encoder velocity
    return this->velocity * this->velFactor;
}

void Encoder::setEncoderType(Encoder::Type encoderType) {
    // Implementation of setEncoderType
    this->type = encoderType;
}

Encoder::Type Encoder::getEncoderType() {
    // Implementation of getEncoderType
    // Return the encoder type (Absolute or Relative)
    return this->type;
}

