/**
 * @file main.cpp
 * @author LyamBRS
 * @brief 
 * Main.cpp file.
 * Your modifications made here WILL NOT
 * be taken into consideration.
 * @version 0.1
 * @date 2024-02-11
 * @copyright Copyright (c) 2024
 */

// - INCLUDES -//
#include <Arduino.h>
#include "Button.h"

/// @brief Arduino's initialisation function.
void setup()
{
    Serial.begin(115200);
}
    Button bouton1(24);
    Button bouton2(22);
    Button bouton3(28);
    Button bouton4(26);


/// @brief Arduino's while(1) function.
void loop()
{
    // Serial.println("allo");

    bouton1.Update();
    bouton2.Update();
    bouton3.Update();
    bouton4.Update();

    if (bouton1.GetState() == false)
    {
        Serial.println("1");
    }

    if (bouton2.GetState() == false)
    {
        Serial.println("2");
    }

    if (bouton3.GetState() == false)
    {
        Serial.println("3");
    }

    if (bouton4.GetState() == false)
    {
        Serial.println("4");
    }
    //delay(500);
}