/**
 * @file BarGraph.h
 * @author LyamBRS
 * @brief 
 * Contains the header definition for the
 * BarGraph class which is used to make a simple
 * digital barGraph and control its inputs.
 * @version 0.1
 * @date 2024-02-11
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include "LED.h"
// - DEFINES - //

// - CLASS - //

/**
 * @brief
 * Class that creates simple BarGraph object allowing
 * you to control a simple digital bargraph through
 * its methods. This allows bits to be parsed as
 * individual LEDs and easy animations to be created.
 */
class BarGraph 
{
    private:
        /**
         * @brief 
         * Array which contains all the LED object
         * that makes up this bar graph
         */
        LED *Leds[10];
        /**
         * @brief 
         * Value that represents all the LEDs of that bar graph.
         */
        int bits;

    public:
        /**
         * @brief Construct a new Bar Graph object
         * Builds a new bar graph while specifying
         * the Arduino's pins for each LED in the 
         * 10 segment bar graph
         * @param pinA 
         * @param pinB 
         * @param pinC 
         * @param pinD 
         * @param pinE 
         * @param pinF 
         * @param pinG 
         * @param pinH 
         * @param pinI 
         * @param pinJ 
         */
        BarGraph(int pinA, int pinB, int pinC, int pinD, int pinE, int pinF, int pinG, int pinH, int pinI, int pinJ);

        /**
         * @brief
         * Returns all the LEDs values as
         * a single int which represent all the
         * bits of that bar graph. 0 to 65472.
         * @return int
         * value representing each LED (0 to 65472)
         */
        int GetBits();

        /**
         * @brief
         * Sets an hexadecimal value as the bit values.
         * @param newBits 
         * @return true:
         * Successfully set the bits to that number.
         * @return false:
         * Specified bits are INVALID
         */
        bool SetBits(int newBits);

        /**
         * @brief
         * Flips all the individual bits
         * and LEDs to the opposite values.
         * @return true:
         * Successfully flipped all 10 LEDs.
         * @return false:
         * Failed to flip all the LEDs of the bar graph
         */
        bool FlipAll();

        /**
         * @brief
         * Turns all LEDS off.
         * Also sets the bits to 0x00.
         * @return true:
         * Successfully turned off all the LEDs.
         * @return false:
         * Failed to turn off all the LEDs
         */
        bool TurnAllOff();

        /**
         * @brief 
         * Turns all 10 LEDs ON.
         * Also sets the bits to ON.
         * @return true:
         * Successfully turned all LEDs on.
         * @return false:
         * Failed to turn all LEDS on.
         */
        bool TurnAllOn();

        /**
         * @brief
         * Returns a single, specified LED's state.
         * @param ledNumber
         * The LED to get the state of (0-9)
         * @return true:
         * That LED is on.
         * @return false:
         * That LED is off rn, it just be like that.
         */
        bool GetIndividualState(int ledNumber);

        /**
         * @brief
         * Sets a single LED to a specified state.
         * Also updates the saved bits.
         * The bar graph SHOULD NOT update the lights.
         * until @ref Update is called.
         * @param ledNumber
         * Which LED (0-9) to change
         * @param wantedState
         * The state that LED should be in.
         * @return true:
         * Successfully changed that LED to the wanted state.
         * @return false:
         * 
         */
        bool SetIndividualState(int ledNumber, bool wantedState);
        
        /**
         * @brief
         * Updates the barGraph object.
         * Sets the LEDs to the needed states based
         * off the bits.
         * @return true:
         * Successfully updated the bargraph.
         * @return false:
         * Failed to update the bar graph.
         */
        bool Update();
};
