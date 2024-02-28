#include "Potentiometer.h"

Potentiometer::Potentiometer(int pin)
{
    if(pin==0)
    {
        canBeUsed = false;
        return;
    }
    delete analogInput;
    analogInput = new AnalogInput(pin);
    canBeUsed = true;
}

bool Potentiometer::SetLimits(int newMin, int newMax){
    if(!canBeUsed) return false;
    analogInput->SetMax(newMax);
    analogInput->SetMin(newMin);
    return true;
}

bool Potentiometer::SetDeadZones(int newDeadZoneMin, int newDeadzoneMax){
    if(!canBeUsed) return false;
    Update();
    int precentValue;
    if(newDeadzoneMax==-1 || newDeadZoneMin==-1){
        GetPourcent();
        return false;
    }
}

float Potentiometer::GetPourcent(){
    if(!canBeUsed) return 0.0f;
    return analogInput->GetPourcent();
}

bool Potentiometer::Update(){
    if(!canBeUsed) return false;
    return analogInput->UpdateRawValue();
}





