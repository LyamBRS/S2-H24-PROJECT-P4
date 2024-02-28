/**
 * @file Potentiometer.h
 * @author LyamBRS
 * @brief 
 * Contains the header definition for the
 * potentiometer class which is used to
 * make a simple analog potentiometer.
 * @version 0.1
 * @date 2024-02-11
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include "AnalogInput.h"

// - DEFINES - //

// - CLASS - //

/**
 * @brief 
 * Potentiometer class. Makes a potentiometer
 * out of one @ref AnalogInput object. Is
 * used to further define how that analog pin
 * is read. Also allows deadzones to be specified.
 */
class Potentiometer 
{
    private:
        /// @brief The analog object that is used to parse the analog input.
        AnalogInput *analogInput;
        /// @brief Specifies the minimum needed before the potentiometer gets stuck at 50. defaults to -1 (disabled)
        int deadZoneMin = -1;
        /// @brief Specifies the maximum needed before the potentiometer gets no longer stuck at 50. defaults to -1 (disabled)
        int deadZoneMax = -1;

        bool canBeUsed = false;

    public:
        /**
         * @brief Construct a new Potentiometer object.
         * Default constuctors sets the deadzones to
         * disabled values (-1). The analog inputs will
         * be set to have a minimum of 0 and a maximum
         * of 1023 for the pourcentage calculations.
         * @param pin
         * The ANALOG pin number where data will be read
         */
        Potentiometer(uint8_t pin);

        /**
         * @brief Construct a new Analog Input object.
         * Advanced constructor which sets the minimum
         * possible as well as maximum possible value
         * to a user defined value. Remember that -1
         * disables deadzones.
         * 
         * @attention
         * Maximum and minimum values SHOULD be verified.
         * 
         * @param pin
         * The ANALOG pin number where data will be read
         * @param minAnalogValue
         * Minimum value that this potentiometer will reach. 0-1023.
         * @param maxAnalogValue
         * Maximum value that this potentiometer will reach. 0-1023.
         * @param minDeadZone
         * Minimum deadzone value. Minimum needed before the potentiometer gets stuck at 50.
         * @param maxDeadZone
         * Maximum deadzone value. Maximum needed before the potentiometer gets no longer stuck at 50.
         */
        Potentiometer(uint8_t pin, int minAnalogValue, int maxAnalogValue, int minDeadZone, int maxDeadZone);

        /**
         * @brief
         * Tries to define a new absolute minimum
         * value that the potentiometer will reach
         * as well as a new absolute maximum value
         * that the potentiometer will reach.
         * @param newMin
         * New minimum value reached by the potentiometer
         * below which it will output 0%
         * @param newMax
         * New maximum value reached by the potentiometer.
         * Above which it will output 100%.
         * @return true:
         * Successfully saved the new values
         * @return false:
         * The minimum or maximum values are NOT valid.
         */
        bool SetLimits(int newMin, int newMax);

        /**
         * @brief
         * Define new maximum and minimum values for the
         * potentiometer deadzone. The deadzone consists
         * of a range where the potentiometer will be stuck
         * at 50%. Setting both to -1 will DISABLE deadzone
         * calculations. 
         * @param newDeadZoneMin
         * Minimum deadzone value. Minimum needed before the potentiometer gets stuck at 50.
         * @param newDeadzoneMax
         * Maximum deadzone value. Maximum needed before the potentiometer gets no longer stuck at 50.
         * @return true:
         * Successfully saved the new deadzone values
         * @return false:
         * The deadzone values are NOT valid.
         */
        bool SetDeadZones(int newDeadZoneMin, int newDeadzoneMax);

        /**
         * @brief
         * Returns the current value of the potentiometer.
         * Value ranges from 0 to 100 and depends on the
         * minimum, maximum as well as deadzones set by you.
         * @attention
         * Calling this function DOES NOT update the values
         * read by the potentiometer object. you MUST call
         * the update function of the potentiometer to
         * update its read values.
         * @return int 
         */
        float GetPourcent();

        /**
         * @brief
         * Updates inputs and outputs of the object.
         * This must be called before values can be read
         * as otherwise, they will have the old values
         * stored in them.
         * @return true:
         * Update was successful.
         * @return false:
         * One or more problems prevent this object from updating.
         */
        bool Update();
};
