/**
 * @file MuonDetector.h
 * @author LyamBRS
 * @brief 
 * Contains the header definition of the
 * Muon Detector class. A little silly
 * goober that reads cosmic rays or some
 * shit because, of course, math.random
 * just isnt enough for us :3.
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
 * Class used to create MuonDetector objects.
 */
class MuonDetector 
{
    private:
        /// @brief The digital arduino pin where the muon detector is connected.
        int arduinoPin;
        /// @brief Total of muons detected
        int totalCounted = 0;

        bool canBeUsed = false;

        int defaultValue = 0;

    public:

        MuonDetector();

        /**
         * @brief Construct a new Muon Detector object.
         * 
         * @param pin 
         */
        MuonDetector(int pin);

        /**
         * @brief
         * Returns how many muons were detected
         * since the last time it was reset.
         * @return int
         * @ref totalCounted
         */
        int GetTotal();

        /**
         * @brief 
         * Resets the deteced muon counter back
         * to 0.
         * @return true:
         * Successfully reset the counter back to 0. 
         * @return false:
         * Failed to reset the counter to 0 / was already at 0.
         */
        bool ResetCount();

        /**
         * @brief 
         * Updates the MuonDetector object.
         * Counts if any muons were detected,
         * @return true:
         * Successfully updated the MuonDetector
         * @return false:
         * Failed to update the MuonDetector
         */
        bool Update();

        int GetAnalog();
};
