/**
 * @file AnalogInput.h
 * @author LyamBRS
 * @brief 
 * Contains the header definition for the
 * joystick class used in this project. The
 * joystick class depends on @ref Potentiometer
 * as well as @ref Button
 * @version 0.1
 * @date 2024-02-11
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include "Button.h"
#include "Potentiometer.h"
// - DEFINES - //

// - CLASS - //

class Joystick 
{
    private:
        /// @brief The button object of the potentiometer
        Button *button;
        /// @brief Y axis potentiometer object
        Potentiometer *xAxis;
        /// @brief X axis potentiometer object
        Potentiometer *yAxis;

        bool canBeUsed = false;

    public:

        Joystick();

        /**
         * @brief Construct a new Joystick object.
         * A joystick consists of 2 potentiometers
         * and 1 button.
         * @param buttonPin
         * Arduino pin number where the button is connected. 
         * @param xAxisPin
         * Arduino pin number where the analog X axis is connected.
         * @param yAxisPin 
         * Arduino pin number where the analog Y axis is connected.
         */
        Joystick(int buttonPin, uint8_t xAxisPin, uint8_t yAxisPin);

        /**
         * @brief Sets new maximum values for all
         * the potentiometers that creates the
         * joystick.
         * @param newMaxX
         * new value from 0 to 1023 that sets the maximum
         * value that the joystick will ever reach for the
         * X axis.
         * @param newMinX
         * new value from 0 to 1023 that sets the minimum
         * value that the joystick will ever reach for the
         * X axis.
         * @return true:
         * Successfully sets the maximums for the potentiometers
         * @return false:
         * Failed to set the maximums for the potentiometers
         */
        bool SetX(int newMaxX, int newMinX);

        /**
         * @brief Sets new minimum values for all
         * the potentiometers that creates the
         * joystick.
         * @param newMaxY
         * new value from 0 to 1023 that sets the maximum
         * value that the joystick will ever reach for the
         * Y axis.
         * @param newMinY
         * new value from 0 to 1023 that sets the minimum
         * value that the joystick will ever reach for the
         * Y axis.
         * @return true:
         * Successfully sets the minimums for the potentiometers
         * @return false:
         * Failed to set the minimums for the potentiometers
         */
        bool SetY(int newMaxY, int newMinY);

        /**
         * @brief
         * Returns the value associated with the
         * potentiometer that makes up the X axis
         * of the joystick.
         * @return int
         * Value ranging from 0 to 100.
         */
        float GetPourcentX();

        /**
         * @brief
         * Returns the value associated with the
         * potentiometer that makes up the Y axis
         * of the joystick.
         * @return int
         * Value ranging from 0 to 100.
         */
        float GetPourcentY();

        /**
         * @brief
         * Returns the state that the joystick's button
         * is in.
         * @return true:
         * The button is pressed 
         * @return false:
         * The button is released
         */
        bool GetButtonState();

        /**
         * @brief 
         * Updates the joystick object.
         * Updates the potentiometers and the
         * button on the joystick.
         * @return true:
         * Successfully updated the joystick
         * @return false:
         * Failed to update the joystick
         */
        bool Update();
};
