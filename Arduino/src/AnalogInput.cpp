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

AnalogInput::AnalogInput(uint8_t pin)
{
    if(pin == 0)
    {
        canBeUsed = false;
        return;
    }
    arduinoPin=pin;
    pinMode(pin,INPUT);
    canBeUsed = true;
}

AnalogInput::AnalogInput(uint8_t pin, int min, int max)
{
    if(pin == 0)
    {
        canBeUsed = false;
        return;
    }

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
    canBeUsed = true;
}

bool AnalogInput::UpdateRawValue()
{
    if(!canBeUsed) return false;
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
    if(!canBeUsed) return false;
    if (1023<newMax || 0<minimumValue)
    {return false;}
    maximumValue=newMax;
    return true;
}

 
bool AnalogInput::SetMin(int newMin)
{
    if(!canBeUsed) return false;
  if (0>newMin||newMin>1023)
    {return false;}
    minimumValue=newMin;
    return true;
}


float AnalogInput::GetPourcent()
{
    if(!canBeUsed) return 0.0f;
    float plage=maximumValue-minimumValue;
    float Valeur_Pourcent=((rawInputValue-minimumValue)/(plage))*100;
    if (Valeur_Pourcent<minimumValue)
    {return 0.0;}
    if (Valeur_Pourcent>maximumValue)
    {return 100.0;}
    return Valeur_Pourcent;
}

