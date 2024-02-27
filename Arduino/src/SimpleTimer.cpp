/**
 * @file SimpleTimer.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-02-27
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "SimpleTimer.h"

// - PROGRAM - //

/**
 * @brief
 * Returns the amount of milliseconds sicne some
 * random ass significant date in the 70s. That
 * doesn't matter, what matters is that we're
 * using this enormous number to make a delta of
 * milliseconds to get a timer.
 * @return uint64_t 
 */
unsigned int SimpleTimer::GetCurrentMilliseconds()
{
    return millis();
}

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
SimpleTimer::SimpleTimer(unsigned int newTimerDurationInMS)
{
    timerDurationMS = newTimerDurationInMS;
    lastCheckedValue = GetCurrentMilliseconds();
    currentValue = GetCurrentMilliseconds();
}

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
bool SimpleTimer::SetDuration(unsigned int newTimerDurationInMS)
{
    lastCheckedValue = GetCurrentMilliseconds();
    currentValue = GetCurrentMilliseconds();
    timerDurationMS = newTimerDurationInMS;
    return true;
}

/**
 * @brief 
 * Resets the timer back to 0.
 * @return true:
 * Successfully reset the timer.
 * @return false:
 * Failed to reset the timer.
 */
bool SimpleTimer::Reset()
{
    lastCheckedValue = GetCurrentMilliseconds();
    currentValue = GetCurrentMilliseconds();
    return true;
}

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
uint64_t SimpleTimer::TimeLeft()
{
    currentValue = GetCurrentMilliseconds();
    uint64_t delta = currentValue - lastCheckedValue;

    if(delta >= timerDurationMS)
    {
        Reset();
        return 0;
    }
    return (timerDurationMS - delta);
}