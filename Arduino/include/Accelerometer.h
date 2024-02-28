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
#include "AnalogInput.h"
// - DEFINES - //

// - CLASS - //

/**
 * @brief 
 * Class which is used to create analog 3.3V
 * 3 axis accelerometer that directly connects
 * to an Arduino's analog pins. No I2C or SPI 
 * here, we're speaking dumb AF accelerometer
 * territory. You wanted to know your G's
 * registers? too bad bro, we're dumb in here.
 */
class Accelerometer 
{
    private:
        /// @brief Object that reads the values of the X axis.
        AnalogInput *xAxis;
        /// @brief Object that reads the values of the Y axis.
        AnalogInput *yAxis;
        /// @brief Object that reads the values of the Z axis.
        AnalogInput *zAxis;

        bool canBeUsed = false;

    public:

        Accelerometer();

        /**
         * @brief Construct a new Accelerometer object.
         * Sets a new analog 3.3V accelerometer.
         * @attention
         * Since we DONT need to know precise angles,
         * this just reads the values as is and doesnt
         * care about it.
         * @param xPin:
         * The arduino pin where the X axis is connected.
         * @param yPin
         * The arduino pin where the Y axis is connected.
         * @param zPin
         * The arduino pin where the Z axis is connected.
         */
        Accelerometer(int xPin, int yPin, int zPin);

        /**
         * @brief Set the Min object
         * Sets new maximum values for all
         * the potentiometers that creates the
         * accelerometer.
         * @param newMaxX
         * New value from 0 to 1023 that sets the maximum
         * value that the X axis will ever reach.
         * @param newMaxY
         * New value from 0 to 1023 that sets the maximum
         * value that the Y axis will ever reach.
         * @param newMaxZ
         * New value from 0 to 1023 that sets the maximum
         * value that the Z axis will ever reach.
         * @return true:
         * New maximum successfully set
         * @return false:
         * Failed to set maximum of the axis.
         */
        bool SetMax(int newMaxX, int newMaxY, int newMaxZ);

        /**
         * @brief Set the Min object
         * Sets new minimum values for all
         * the potentiometers that creates the
         * accelerometer.
         * @param newMinX
         * New value from 0 to 1023 that sets the minimum
         * value that the X axis will ever reach.
         * @param newMinY
         * New value from 0 to 1023 that sets the minimum
         * value that the Y axis will ever reach.
         * @param newMinZ
         * New value from 0 to 1023 that sets the minimum
         * value that the Z axis will ever reach.
         * @return true:
         * New minimums successfully set
         * @return false:
         * Failed to set minimums of the axis.
         */
        bool SetMin(int newMinX, int newMinY, int newMinZ);

        /**
         * @brief
         * Returns the value associated with the
         * potentiometer that makes up the X axis
         * of the accelerometer.
         * @return int
         * Value ranging from 0 to 100.
         */
        int GetPourcentX();

        /**
         * @brief
         * Returns the value associated with the
         * potentiometer that makes up the Y axis
         * of the accelerometer.
         * @return int
         * Value ranging from 0 to 100.
         */
        int GetPourcentY();

        /**
         * @brief
         * Returns the value associated with the
         * potentiometer that makes up the Z axis
         * of the accelerometer.
         * @return int
         * Value ranging from 0 to 100.
         */
        int GetPourcentZ();

        /**
         * @brief 
         * Updates the accelerometer object.
         * Updates the accelerometer and the
         * button on the joystick.
         * @return true:
         * Successfully updated the accelerometer
         * @return false:
         * Failed to update the accelerometer
         */
        bool Update();
};
