#include "LED.h"
#include <Arduino.h>

//arduino pin Output??

LED::LED(){
}

LED::LED(int pin){
    if(pin==0)
    {
        canBeUsed = false;
        return;
    }
    arduinoPin = pin;
    pinMode(arduinoPin, OUTPUT);
    canBeUsed = true;
}

LED::LED(int pin, bool initialState){
    if(pin==0)
    {
        canBeUsed = false;
        return;
    }
    arduinoPin = pin;
    pinMode(arduinoPin, OUTPUT);
    state = initialState;
    canBeUsed = true;
}

LED::LED(int pin, bool initialState, bool inverted){
    if(pin==0)
    {
        canBeUsed = false;
        return;
    }
    arduinoPin = pin;
    pinMode(arduinoPin, OUTPUT);
    state = initialState;
    isInverted=inverted;
    canBeUsed = true;
}

bool LED::TurnOn(){
    if(!canBeUsed) return false;

    if (state == false)
    {
        state = true;
        return true;
    }
    return false;
}

bool LED::TurnOff(){
    if(!canBeUsed) return false;
    if (state == true)
    {
        state = false;
        return true;
    }
    return false;
}

bool LED::FlipState(){
    if(!canBeUsed) return false;
    state = !state;
    return true;
}

bool LED::GetState(){
    if(!canBeUsed) return false;
    return state;
}

bool LED::Update()
{
    if(!canBeUsed) return false;
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