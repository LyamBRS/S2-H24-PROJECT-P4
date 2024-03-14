/**
 * @file SimpleChrono.cpp
 * @author LyamBRS
 * @brief
 * Holds a spin-off of
 * @ref SimpleTimer which
 * counts up instead.
 * @version 0.1
 * @date 2024-03-12
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "SimpleChrono.h"

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
uint64_t SimpleChrono::GetTimeSinceEpoch()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

/**
 * @brief 
 * # SimpleChrono
 * @brief 
 * Simple class which is used to create basic
 * Chronos by using STD chrono library to
 * calculate the time difference between two
 * function calls. You can manually reset it,
 * start, stop, get seconds, minutes, hours.
 */
SimpleChrono::SimpleChrono()
{
    
}

/**
 * @brief 
 * Resets the chrono back to 0.
 * @return true:
 * Successfully reset the chrono.
 * @return false:
 * Failed to reset the chrono.
 */
bool SimpleChrono::Reset()
{
    valueAtStop = GetTimeSinceEpoch();
    valueAtStart = GetTimeSinceEpoch();
    currentValue = GetTimeSinceEpoch();
    return true;
}

/**
 * @brief 
 * Returns how much milliseconds there has been
 * since @ref Start was called.
 * @return uint64_t
 * How long it has been, in milliseconds
 */
uint64_t SimpleChrono::GetTotalTime()
{
    if(!isStarted) return 0; // Not running, its 0.
    if(isPaused) return valueAtStop - valueAtStart;

    currentValue = GetTimeSinceEpoch();
    return currentValue - valueAtStart;
}

/**
 * @brief 
 * Returns how many seconds it has been
 * since @ref Start was called.
 * @attention
 * This returns a number from 0 to 59
 * and is used when you want to display
 * a time with the 00:00:00 format.
 * @return uint64_t
 * How many seconds since the last minute
 */
uint8_t SimpleChrono::GetClockSeconds()
{
    uint64_t totalMS = GetTotalTime();
    return (totalMS/1000)%60;
}

/**
 * @brief 
 * Returns how many minutes it has been
 * since @ref Start was called.
 * @attention
 * This returns a number from 0 to 59
 * and is used when you want to display
 * a time with the 00:00:00 format.
 * @return uint64_t
 * How many minutes since the last minute
 */
uint8_t SimpleChrono::GetClockMinutes()
{
    uint64_t totalMS = GetTotalTime();
    return ((totalMS/1000)/60)%60;
}

/**
 * @brief 
 * Returns how many minutes it has been
 * since @ref Start was called.
 * @attention
 * This returns an int number
 * and is used when you want to display
 * a time with the 00000000:00:00 format.
 * @return uint64_t
 * How many minutes since the last minute
 */
uint8_t SimpleChrono::GetClockHours()
{
    uint64_t totalMS = GetTotalTime();
    return ((totalMS/1000)/60)/60;
}

/**
 * @brief 
 * Stops the chrono. You can resume it by
 * calling @ref Resume. There's not much
 * else to say, if you dont know how a
 * standard chronometer works... euuh..
 * Figure it out on your phone? Its the same.
 * @return true
 * Successfully stopped the chrono
 * @return false
 * Unecessary
 */
bool SimpleChrono::Stop()
{
    if(!isStarted) return false;
    if(isPaused) return false;
    isPaused = true;
    valueAtStop = GetTimeSinceEpoch();
    return true;
}

/**
 * @brief 
 * Resumes the chrono. You can stop it by
 * calling @ref Stop. There's not much
 * else to say, if you dont know how a
 * standard chronometer works... euuh..
 * Figure it out on your phone? Its the same.
 * @return true
 * Successfully resumed the chrono
 * @return false
 * Unecessary, wasnt stopped/started
 * @warning
 * ## This DOES NOT start the chrono.
 */
bool SimpleChrono::Resume()
{
    if(!isStarted) return false;
    if(!isPaused) return false;
    isPaused = false;
    return true;
}

/**
 * @brief 
 * Starts the chrono. You can stop it by
 * calling @ref Stop. and reset it without
 * stopping by calling @ref Reset. 
 * There's not much else to say, if you dont 
 * know how a standard chronometer works... euuh..
 * Figure it out on your phone? Its the same.
 * @return true
 * Successfully stopped the chrono
 * @return false
 * Unecessary.
 * @warning
 * Will reset the chrono if called while its going.
 */
bool SimpleChrono::Start()
{
    Reset();
    isPaused = false;
    isStarted = true;
    valueAtStart = GetTimeSinceEpoch();
    return true;
}