/**
 * @file Button.cpp
 * @author Anthony & François
 * @brief
 * @version 0.1
 * @date 2024-02-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Button.h"
#include <Arduino.h>

Button::Button()
{
}

Button::Button(int pin)
{
    if(pin == 0)
    {
        canBeUsed = false;
        return;
    }
    arduinoPin = pin;
    pinMode(arduinoPin, INPUT);
    canBeUsed = true;
}

Button::Button(int pin, bool shouldBeInverted, int debounceDelayMS)
{
    if(pin == 0)
    {
        canBeUsed = false;
        return;
    }
    isInverted = shouldBeInverted;
    arduinoPin = pin;
    canBeUsed = true;
}

Button::~Button()
{
    canBeUsed = false;
}

bool Button::GetState()
{
    if(!canBeUsed) return false;
    return state;
}

bool Button::Update()
{
    if(!canBeUsed) return false;
    state = digitalRead(arduinoPin);
    if(isInverted)
    {
        state = !state;
    }
    return true;
}
void Button::SetState()
{
    if(!canBeUsed) return;
    bool res = digitalRead(arduinoPin);
    if(res)
    {
        state = !state;
    }

    if (res == HIGH)
    {
        state = true;
    }
    else
    {
        state = false;
    }
}