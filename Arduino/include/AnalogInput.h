/**
 * @file AnalogInput.h
 * @author LyamBRS
 * @brief 
 * Contains the header definition for the
 * AnalogInput class which is used to quickly
 * make an analog input into another arduino
 * component without having to remake methods
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
 * Used to make an handler for an analog input on
 * an Arduino. This way, pourcentage value based
 * on read data is automatically calculated when
 * the getter function is called.
 * This allows quick object creation that would
 * depend on one or more analog pins thus reducing
 * time spent redoing the same shit over and over.
 */
class AnalogInput 
{
    private:
        /// @brief The pin number where the analog data will be read. -1 by default.
        int arduinoPin = -1;
        /// @brief The last raw input that was gathered when @ref UpdateRawValue was called.
        int rawInputValue = 0;
        /// @brief The absolute lowest that the input value can reach. Anything below will be seen as 0.
        int minimumValue = 0;
        /// @brief The absolute maximum that the input value can reach. Anything above will be seen as 100. Defaults to 1023.
        int maximumValue = 1023;

    public:
        /**
         * @brief Construct a new Analog Input object.
         * Default constuctors sets the minimum possible
         * value to 0 and the maximum possible value
         * to 1023.
         * @param pin
         * The ANALOG pin number where data will be read
         */
        AnalogInput(int pin);

        /**
         * @brief Construct a new Analog Input object.
         * Advanced constructor which sets the minimum
         * possible as well as maximum possible value
         * to a user defined value.
         * 
         * @attention
         * Maximum and minimum values SHOULD be verified.
         * 
         * @param pin
         * The ANALOG pin number where data will be read
         * @param min
         * Minimum value that this input will reach. 0-1023.
         * @param max
         * Maximum value that this input will reach. 0-1023.
         */
        AnalogInput(int pin, int min, int max);

        /**
         * @brief 
         * Function that simply reads the analog pin value
         * and stores that in @ref rawInputValue.
         * This is the ONLY WAY to update the value.
         * @ref GetPourcent WILL NOT update the value.
         * @return true:
         * Successfully updated the value.
         * @return false:
         * Failed to update the value (due to arduino pin number OR minValue OR maxValue)
         */
        bool UpdateRawValue();

        /**
         * @brief
         * Define a new maximum that the analog pin can read
         * @param newMax
         * Value from 0 to 1023 that defines the absolute maximum
         * that this analog input will ever read.
         * @return true:
         * Successfully changed the maximum to a new value.
         * @return false:
         * The specified value CANNOT BE USED.
         */
        bool SetMax(int newMax);

        /**
         * @brief
         * Define a new minimum that the analog pin can read
         * @param newMin
         * Value from 0 to 1023 that defines the absolute minimum
         * that this analog input will ever read.
         * @return true:
         * Successfully changed the minimum to a new value.
         * @return false:
         * The specified value CANNOT BE USED.
         */      
        bool SetMin(int newMin);

        /**
         * @brief
         * Returns a value ranging from 0 to 100 based on
         * the last value that was read through @ref UpdateRawValue.
         * The value is calculated based off the minimum
         * and maximum defined in this function.
         * @return int
         * Value from 0 to 100.
         */
        int GetPourcent();
};
