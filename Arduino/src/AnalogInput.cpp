#include "../include/AnalogInput.h"
#include <Arduino.h>

AnalogInput::AnalogInput(int pin)
{
    arduinoPin=pin;
    pinMode(pin,INPUT);
}

AnalogInput::AnalogInput(int pin, int min, int max)
{
    pinMode(pin,INPUT);
    arduinoPin=pin;
    minimumValue=min;
    maximumValue=max;
}

bool AnalogInput::UpdateRawValue()
{
    rawInputValue=analogRead(arduinoPin);
    if (rawInputValue==NULL)
    {
        return false;
    }
    else
    return true;
}

bool AnalogInput::SetMax(int newMax)
{
    if (maximumValue<newMax || newMax<minimumValue)
    {return false;}
    maximumValue=newMax;
    return true;
}

 
bool AnalogInput::SetMin(int newMin)
{
  if (minimumValue>newMin||newMin>maximumValue)
    {return false;}
    maximumValue=newMin;
    return true;
}


int AnalogInput::GetPourcent()
{
    if (rawInputValue<minimumValue)
    {return 0;}
    if (rawInputValue>maximumValue)
    {return 100;}
    int Valeur_Pourcent=((rawInputValue-minimumValue)*100/(maximumValue-(minimumValue)));
    return Valeur_Pourcent;
}

