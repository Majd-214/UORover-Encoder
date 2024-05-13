/*
Relative/Absolute Encoder Library using Arduino Framework
Developed for the University of Ottawa Rover Team (UORover)

UORover Encoder Library © 2023 by Majd Aburas is licensed under
Attribution 4.0 International.
To view a copy of this license, visit http://creativecommons.org/licenses/by/4.0/
*/

#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"

class Encoder {
public:
    enum Type {
        Absolute, Quadrature, Alternate
    };

    explicit Encoder(byte ABS);

    Encoder(byte A, byte B);

    Encoder(byte A, byte B, byte Index);

    Encoder(byte A, byte B, byte Index, byte ABS);

    Encoder(byte A, byte B, byte Index, byte ABS, Type type);

    void begin() const;

    void update();

    void readQuadrature();

    void setInverted(bool state);

    bool getInverted() const;

    void setZeroOffset(double offset);

    double getZeroOffset() const;

    void setPositionConversionFactor(double factor);

    double getPositionConversionFactor() const;

    void setVelocityConversionFactor(double factor);

    double getVelocityConversionFactor() const;

    void setPosition(double newPosition);

    double getPosition() const;

    double getVelocity() const;

    void setEncoderType(Type encoderType);

    Type getEncoderType();

private:
    byte A;
    byte B;
    byte Index;
    byte ABS;
    bool inverted;
    double zeroOffset;
    double position;
    double posFactor;
    double velocity;
    double velFactor;
    double prevPosition;
    unsigned long prevTime;
    Type type;
};

#endif
