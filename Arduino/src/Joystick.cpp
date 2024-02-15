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

Joystick::Joystick(int buttonPin, int xAxisPin, int yAxisPin)
{
    button = new Button(buttonPin);
    xAxis = new Potentiometer(xAxisPin);
    yAxis = new Potentiometer(yAxisPin);
}

bool Joystick::SetX(int newMaxX, int newMinX)
{
    xAxis->SetLimits(newMaxX, newMinX);
    return true;
}

bool Joystick::SetY(int newMaxY, int newMinY)
{
    yAxis->SetLimits(newMaxY, newMinY);
    return true;
}

float Joystick::GetPourcentX()
{
    return xAxis->GetPourcent();
}

float Joystick::GetPourcentY()
{
    return yAxis->GetPourcent();
}

bool Joystick::GetButtonState()
{
    return button->GetState();
}

bool Joystick::Update()
{
    xAxis->Update();
    yAxis->Update();
    button->Update();
    return true;
}

