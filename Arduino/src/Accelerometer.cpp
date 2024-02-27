#include "Accelerometer.h"
#include <Arduino.h>
    
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
