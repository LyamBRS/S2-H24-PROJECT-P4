#include "Accelerometer.h"

    Accelerometer::Accelerometer(int xPin, int yPin, int zPin){
        xAxis = new AnalogInput(xPin);
        yAxis = new AnalogInput(yPin);
        zAxis = new AnalogInput(zPin);
    }

    bool Accelerometer::SetMax(int newMaxX, int newMaxY, int newMaxZ){
        xAxis->SetMax(newMaxX);
        yAxis->SetMax(newMaxY);
        zAxis->SetMax(newMaxZ);
        return true;
    }

    bool Accelerometer::SetMin(int newMinX, int newMinY, int newMinZ){
        xAxis->SetMin(newMinX);
        yAxis->SetMin(newMinY);
        zAxis->SetMin(newMinZ);
        return true;
    }

    int Accelerometer::GetPourcentX(){
        xAxis->UpdateRawValue();
        return (xAxis->GetPourcent());
    }

    int Accelerometer::GetPourcentY(){
        yAxis->UpdateRawValue();
        return (yAxis->GetPourcent());
    }

    int Accelerometer::GetPourcentZ(){
        zAxis->UpdateRawValue();
        return (zAxis->GetPourcent());
    }

    bool Accelerometer::Update(){
        xAxis->UpdateRawValue();
        yAxis->UpdateRawValue();
        zAxis->UpdateRawValue();
        return true;
    }


