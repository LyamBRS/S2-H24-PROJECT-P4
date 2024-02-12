/**
 * @file Button.h
 * @author LyamBRS
 * @brief 
 * Contains the header definition for the
 * Button class which is used to make a simple
 * digital button and control its inputs.
 * @version 0.1
 * @date 2024-02-11
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include <Arduino.h>
// - DEFINES - //

// - CLASS - //

/**
 * @brief
 * Class that creates simple Button object allowing
 * you to control a simple digital button through
 * its methods. This allows programmable debounces
 * and handle a button if its state is inverted.
 */
class Button 
{
    private:
        /// @brief The digital pin number on the arduino where this LED will be connected.
        uint8_t arduinoPin;
        /// @brief The last state that was read when Update was called.
        bool state = false;
        /// @brief Specifies if the button is on with a LOW value. Defaults to false (ON with a HIGH value)
        bool isInverted = false;
        /// @brief How long until the button is no longer seen as HIGH.
        int debounceTimer = 0;

    public:
        /**
         * @brief Construct a new Button object.
         * Default constructor only sets the pin
         * of the button to a specified number
         * associated with the arduino's pins.
         * The button is not set to inverted by default.
         * Debounce is turned off by default
         * @param pin
         * Arduino pin number where this button is plugged.
         */
        Button(int pin);


        /**
         * @brief Construct a new Button object.
         * Default constructor sets the pin
         * of the button to a specified number
         * associated with the arduino's pins.
         * Also sets the button's inverted state
         * meaning it should or shoudlnt be pressed
         * with a low value.
         * Also sets how long of a debounce this
         * button should have in milliseconds.
         * @param pin
         * Arduino pin number where this button is plugged.
         * @param isInverted
         * Defines if the button is pressed when a low value is read
         * @param debounceDelayMS
         * How long in milliseconds should the debounce be for.
         */
        Button(int pin, bool isInverted, int debounceDelayMS);

        /**
         * @brief Destroy the Button object
         * 
         */
        ~Button();

        /**
         * @brief Get the State of the button.
         * Is returned based off @ref Update.
         * The value is debounced and is TRUE
         * as long as the button is bouncing.
         * @return true:
         * It be pressed fr.
         * @return false:
         * Depressed button :(
         */
        bool GetState();

        /**
         * @brief
         * Updates the button object.
         * @return true:
         * Successfully updated the button. (get its state)
         * @return false:
         * Failed to update the button.
         */
        bool Update();

        /**
         * @brief Set the State object
         * 
         */
        void SetState();
};
