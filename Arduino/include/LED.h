/**
 * @file LED.h
 * @author LyamBRS
 * @brief 
 * Contains the header definition for the
 * LED class which is used to make a simple
 * digital LED and control its state.
 * @version 0.1
 * @date 2024-02-11
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //

// - DEFINES - //

// - CLASS - //

/**
 * @brief
 * Class that creates simple LED object allowing
 * you to control a simple digital LED through
 * its methods. This also allows LEDs that are
 * driven through LOW instead of HIGH to be
 * compensated.
 */
class LED 
{
    private:
        /// @brief The digital pin number on the arduino where this LED will be connected.
        int arduinoPin;
        /// @brief The last state that was set to this LED
        bool state = false;
        /// @brief Specifies if the LED is on with a LOW value. Defaults to false (ON with a HIGH value)
        bool isInverted = false;

    public:

        LED();

        /**
         * @brief Construct a new LED object.
         * Only sets the arduino pin associated with
         * the LED. The LED is not inverted by default.
         * @param pin 
         */
        LED(int pin);

        /**
         * @brief Construct a new LED object.
         * Sets the arduino pin number associated with
         * the LED as well as the initial state that the
         * LED must have at the start of the program.
         * The LED will not be inverted by default.
         * @param pin
         * Arduino pin number where this LED is plugged.
         * @param initialState
         * Should the LED be ON or OFF by default?
         */
        LED(int pin, bool initialState);

        /**
         * @brief Construct a new LED object.
         * Sets the arduino pin number associated with
         * the LED as well as the initial state that the
         * LED must have at the start of the program.
         * Also sets wether the LED is on with a LOW or
         * on with a HIGH.
         * @param pin
         * Arduino pin number where this LED is plugged.
         * @param initialState
         * Should the LED be ON or OFF by default?
         * @param isInverted
        * Specifies if the LED is on with a LOW value. Defaults to false (ON with a HIGH value)
         */
        LED(int pin, bool initialState, bool inverted);

        /**
         * @brief
         * Sets the LED state to be ON.
         * @return true
         * The LED is now ON.
         * @return false:
         * The LED failed to be turned on OR was already ON.
         */
        bool TurnOn();

        /**
         * @brief
         * Sets the LED state to be OFF.
         * @return true
         * The LED is now OFF.
         * @return false:
         * The LED failed to be turned off OR was already OFF.
         */  
        bool TurnOff();

        /**
         * @brief 
         * Flips the state of the LED to be the
         * opposite of what it currently is.
         * @return true:
         * Successfully inverted the LED state.
         * @return false:
         * An error occured and the state could
         * not be inverted.
         */
        bool FlipState();

        /**
         * @brief
         * Returns the last state of the LED.
         * this DOES NOT read the digital pin.
         * @return true:
         * The LED is currently ON.
         * @return false:
         * The LED is currently OFF.
         */
        bool GetState();

        /**
         * @brief
         * Updates the LED object.
         * @return true:
         * Successfully updated the LED.
         * @return false:
         * Failed to update the LED.
         */
        bool Update();
};
