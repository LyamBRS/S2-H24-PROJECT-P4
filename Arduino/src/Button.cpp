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

Button::Button(int pin, bool isInverted, int debounceDelayMS)
{
    if(pin == 0)
    {
        canBeUsed = false;
        return;
    }
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
    return true;
}
void Button::SetState()
{
    if(!canBeUsed) return;
    int res = digitalRead(arduinoPin);

    if (res == HIGH)
    {
        state = true;
    }
    else
    {
        state = false;
    }
}