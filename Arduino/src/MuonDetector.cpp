/**
 * @file MuonDetector.cpp
 * @author LyamBRS
 * @brief 
 * Contains the header definition of the
 * Muon Detector class. A little silly
 * goober that reads cosmic rays or some
 * shit because, of course, math.random
 * just isnt enough for us :3.
 * @version 0.1
 * @date 2024-02-27
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "MuonDetector.h"

// - PROGRAM - //

MuonDetector::MuonDetector()
{

}

/**
 * @brief Construct a new Muon Detector object.
 * 
 * @param pin 
 */
MuonDetector::MuonDetector(int pin)
{
    // AMOGUS
}

/**
 * @brief
 * Returns how many muons were detected
 * since the last time it was reset.
 * @return int
 * @ref totalCounted
 */
int MuonDetector::GetTotal()
{
    return 0;
}

/**
 * @brief 
 * Resets the deteced muon counter back
 * to 0.
 * @return true:
 * Successfully reset the counter back to 0. 
 * @return false:
 * Failed to reset the counter to 0 / was already at 0.
 */
bool MuonDetector::ResetCount()
{
    return false;
}

/**
 * @brief 
 * Updates the MuonDetector object.
 * Counts if any muons were detected,
 * @return true:
 * Successfully updated the MuonDetector
 * @return false:
 * Failed to update the MuonDetector
 */
bool MuonDetector::Update()
{
    return false;
}

