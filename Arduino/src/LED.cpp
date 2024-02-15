#include "LED.h"
#include <Arduino.h>

LED::LED(int pin){
    arduinoPin = pin;
}

LED::LED(int pin, bool initialState){
    arduinoPin = pin;
    state = initialState;
}

LED::LED(int pin, bool initialState, bool inverted){
    arduinoPin = pin;
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
    if(state == true){
        state = false;
    }else{
        state = true;
    }
    return true;
}

bool LED::GetState(){
    return state;
}

bool LED::Update()
{
    int resultat = digitalRead(arduinoPin);
    if (GetState() == true)
    {
        resultat = HIGH;
    }
    else
    {
        resultat = LOW;
    }
    return true;
}
    