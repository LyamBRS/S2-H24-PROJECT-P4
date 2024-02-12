#include "Potentiometer.h"

Potentiometer::Potentiometer(int pin)
{
    delete analogInput;
    analogInput = new AnalogInput(pin);
}

bool Potentiometer::SetLimits(int newMin, int newMax){
    analogInput->SetMax(newMax);
    analogInput->SetMin(newMin);
    return true;
}

bool Potentiometer::SetDeadZones(int newDeadZoneMin, int newDeadzoneMax){
    Update();
    int precentValue;
    if(newDeadzoneMax==-1 || newDeadZoneMin==-1){
        GetPourcent();
        return false;
    }
}

int Potentiometer::GetPourcent(){
    return analogInput->GetPourcent();
}

bool Potentiometer::Update(){
    //rawInputValue = analogInput.UpdateRawValue();
}





