#include "Accelerometer.h"
#include <Arduino.h>

Accelerometer::Accelerometer()
{
}

Accelerometer::Accelerometer(int xPin, int yPin, int zPin)
{
    xAxis = new AnalogInput(xPin);
    yAxis = new AnalogInput(yPin);
    zAxis = new AnalogInput(zPin);
}

int Accelerometer::GetPourcentX(){
    return (xAxis->GetPourcent());
}

int Accelerometer::GetPourcentY(){
    return (yAxis->GetPourcent());
}

int Accelerometer::GetPourcentZ(){
    return (zAxis->GetPourcent());
}

bool Accelerometer::Update(){
    xAxis->UpdateRawValue();
    yAxis->UpdateRawValue();
    zAxis->UpdateRawValue();
    return true;
}
