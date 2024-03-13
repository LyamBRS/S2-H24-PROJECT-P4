/**
 * @file SimpleChrono.h
 * @author LyamBRS
 * @brief
 * Holds a spin-off of
 * @ref SimpleTimer which
 * counts up instead.
 * @version 0.1
 * @date 2024-03-12
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
 * # SimpleChrono
 * @brief 
 * Simple class which is used to create basic
 * Chronos by using STD chrono library to
 * calculate the time difference between two
 * function calls. You can manually reset it,
 * start, stop, get seconds, minutes, hours.
 * @warning
 * stop, resume as well as hours are not coded yet.
 */
class SimpleChrono
{
    private:
        uint64_t valueAtStop = 0;
        uint64_t valueAtStart = 0;
        uint64_t currentValue = 0;

        bool isStarted = false;
        bool isPaused = false;

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
         * # SimpleChrono
         * @brief 
         * Simple class which is used to create basic
         * Chronos by using STD chrono library to
         * calculate the time difference between two
         * function calls. You can manually reset it,
         * start, stop, get seconds, minutes, hours.
         */
        SimpleChrono();

        /**
         * @brief 
         * Resets the chrono back to 0.
         * @return true:
         * Successfully reset the chrono.
         * @return false:
         * Failed to reset the chrono.
         */
        bool Reset();

        /**
         * @brief 
         * Returns how much milliseconds there has been
         * since @ref Start was called.
         * @return uint64_t
         * How long it has been, in milliseconds
         */
        uint64_t GetTotalTime();

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
        uint8_t GetClockSeconds();

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
        uint8_t GetClockMinutes();

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
        uint8_t GetClockHours();

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
        bool Stop();

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
        bool Resume();

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
        bool Start();
};