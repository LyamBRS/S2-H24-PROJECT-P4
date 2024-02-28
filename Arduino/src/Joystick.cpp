/**
 * @file Joystick.cpp
 * @author Anthony & Adam & Isac & Victor
 * @brief
 * @version 0.1
 * @date 2024-02-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <Arduino.h>
#include "Joystick.h"

Joystick::Joystick()
{

}

Joystick::Joystick(int buttonPin, uint8_t xAxisPin, uint8_t yAxisPin)
{
    button = new Button(buttonPin);
    xAxis = new Potentiometer(xAxisPin);
    yAxis = new Potentiometer(yAxisPin);
    canBeUsed = true;
}

bool Joystick::SetX(int newMaxX, int newMinX)
{
    if(!canBeUsed) return false;
    xAxis->SetLimits(newMaxX, newMinX);
    return true;
}

bool Joystick::SetY(int newMaxY, int newMinY)
{
    if(!canBeUsed) return false;
    yAxis->SetLimits(newMaxY, newMinY);
    return true;
}

float Joystick::GetPourcentX()
{
    if(!canBeUsed) return 0.0f;
    return xAxis->GetPourcent();
}

float Joystick::GetPourcentY()
{
    if(!canBeUsed) return 0.0f;
    return yAxis->GetPourcent();
}

bool Joystick::GetButtonState()
{
    if(!canBeUsed) return false;
    return button->GetState();
}

bool Joystick::Update()
{
    if(!canBeUsed) return false;
    xAxis->Update();
    yAxis->Update();
    button->Update();
    return true;
}

