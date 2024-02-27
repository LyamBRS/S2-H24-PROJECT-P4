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
    arduinoPin = pin;
    pinMode(arduinoPin, INPUT);
}

Button::Button(int pin, bool isInverted, int debounceDelayMS)
{
    arduinoPin = pin;
}

Button::~Button()
{

}

bool Button::GetState()
{
    return state;
}

bool Button::Update()
{
    state = digitalRead(arduinoPin);
    return true;
}
void Button::SetState()
{
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