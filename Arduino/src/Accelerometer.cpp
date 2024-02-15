#include "../include/AnalogInput.h"
#include <Arduino.h>

/**
 * @brief Construct a new Analog Input object.
 * This constructor DOES NOT DO ANYTHING.
 * YOU MUST build a new object if this one is
 * called.
 */
AnalogInput::AnalogInput()
{
    // DOES NOTHING ON PURPOSE.
}

AnalogInput::AnalogInput(int pin)
{
    arduinoPin=pin;
    pinMode(pin,INPUT);
}

AnalogInput::AnalogInput(int pin, int min, int max)
{
    pinMode(pin,INPUT);
    arduinoPin=pin;
     if (min<0)
    {min=0;}
    if (max>1023)
    {max=1023;}
      if (min>=1023)
    {min=1022;}
      if (max<=0)
    {max=1;}
    if (max>1023)
    {max=1023;}
    minimumValue=min;
    maximumValue=max;
}

bool AnalogInput::UpdateRawValue()
{
    rawInputValue=analogRead(arduinoPin);
    if (rawInputValue>maximumValue||rawInputValue<minimumValue)
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


float AnalogInput::GetPourcent()
{
    float Valeur_Pourcent=(((rawInputValue)-minimumValue)/maximumValue-minimumValue);
    return Valeur_Pourcent*100;
    if (Valeur_Pourcent<minimumValue)
    {return 0.0;}
    if (Valeur_Pourcent>maximumValue)
    {return 100.0;}
}
