#include "LED.h"
#include <Arduino.h>

//arduino pin Output??

LED::LED(){
}

LED::LED(int pin){
    arduinoPin = pin;
    pinMode(arduinoPin, OUTPUT);
}

LED::LED(int pin, bool initialState){
    arduinoPin = pin;
    pinMode(arduinoPin, OUTPUT);
    state = initialState;
}

LED::LED(int pin, bool initialState, bool inverted){
    arduinoPin = pin;
    pinMode(arduinoPin, OUTPUT);
    state = initialState;
    isInverted=inverted;
}

bool LED::TurnOn(){
    if (state == false)
    {
        state = true;
        return true;
    }
    return false;
}

bool LED::TurnOff(){
    if (state == true)
    {
        state = false;
        return true;
    }
    return false;
}

bool LED::FlipState(){
    state = !state;
    return true;
}

bool LED::GetState(){
    return state;
}

bool LED::Update()
{
    if (GetState() == true)
    {
        digitalWrite(arduinoPin, HIGH);
    }
    else
    {
        digitalWrite(arduinoPin, LOW);
    }
    return true;
}