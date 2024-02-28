#include "Accelerometer.h"
#include <Arduino.h>

Accelerometer::Accelerometer()
{
}

Accelerometer::Accelerometer(uint8_t xPin, uint8_t yPin, uint8_t zPin)
{
    xAxis = new AnalogInput(xPin);
    yAxis = new AnalogInput(yPin);
    zAxis = new AnalogInput(zPin);

    canBeUsed = true;
}

int Accelerometer::GetPourcentX(){
    if(!canBeUsed)return 0;
    return (xAxis->GetPourcent());
}

int Accelerometer::GetPourcentY(){
    if(!canBeUsed)return 0;
    return (yAxis->GetPourcent());
}

int Accelerometer::GetPourcentZ(){
    if(!canBeUsed)return 0;
    return (zAxis->GetPourcent());
}

bool Accelerometer::Update(){
    if(!canBeUsed)return false;
    xAxis->UpdateRawValue();
    yAxis->UpdateRawValue();
    zAxis->UpdateRawValue();
    return true;
}
