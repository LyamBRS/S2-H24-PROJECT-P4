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

