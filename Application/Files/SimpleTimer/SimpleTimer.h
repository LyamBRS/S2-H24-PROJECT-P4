/**
 * @file Timer.h
 * @author LyamBRS
 * @brief
 * Header file used to define the @ref SimpleTimer
 * class which is used to create simple timers
 * basde on EPOCH time through STD chrono
 * library.
 * @version 0.1
 * @date 2024-02-14
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include <chrono>
#include <cstdint>
#include <iostream>

// - DEFINES - //

// - CLASS - //

/**
 * @brief 
 * # SimpleTimer
 * @brief 
 * Simple class which is used to create basic
 * Timers by using STD chrono library to
 * calculate the time difference between two
 * function calls. You must specify how long
 * in milliseconds the timer should last for.
 * @brief 
 * ## Example:
 * @brief
 * - if(timerName.TimeLeft() == 0)
 * @brief
 * - {//Do stuff (automatic reset when TimeLeft called)}
 */
class SimpleTimer
{
    private:
        /// @brief Stores how long the timer should be going for.
        uint64_t timerDurationMS = 0;

        uint64_t lastCheckedValue = 0;
        uint64_t currentValue = 0;

        /**
         * @brief
         * Returns the amount of milliseconds sicne some
         * random ass significant date in the 70s. That
         * doesn't matter, what matters is that we're
         * using this enormous number to make a delta of
         * milliseconds to get a timer.
         * @return uint64_t 
         */
        uint64_t GetTimeSinceEpoch();
    public:

        /**
         * @brief 
         * # SimpleTimer
         * @brief 
         * Simple class which is used to create basic
         * Timers by using STD chrono library to
         * calculate the time difference between two
         * function calls. You must specify how long
         * in milliseconds the timer should last for.
         * @brief 
         * ## Example:
         * @brief
         * - if(timerName.TimeLeft() == 0)
         * @brief
         * - {//Do stuff (automatic reset when TimeLeft called)}
         * @param newTimerDurationInMS
         * How long should the timer be for?
         */
        SimpleTimer(uint64_t newTimerDurationInMS);

        /**
         * @brief
         * Sets a new duration in milliseconds.
         * Will also reset the timer back to 0.
         * @param newTimerDurationInMS 
         * @return true:
         * Successfully set a new duration to the timer.
         * @return false:
         * Failed to set a new duration to the timer.
         */
        bool SetDuration(uint64_t newTimerDurationInMS);

        /**
         * @brief 
         * Resets the timer back to 0.
         * @return true:
         * Successfully reset the timer.
         * @return false:
         * Failed to reset the timer.
         */
        bool Reset();

        /**
         * @brief 
         * Returns how much milliseconds are left before
         * the timer reaches 0. The timer will stay at 0
         * until this function is called after which it
         * will automatically reset back to its specified
         * value for you.
         * @return uint64_t
         * How long until it reaches 0 (milliseconds) 
         */
        uint64_t TimeLeft();

        uint64_t TimeLeftNoReset();
};