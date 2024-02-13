/**
 * @file Movements.h
 * @author LyamBRS
 * @brief
 * Header definition of the movement
 * class which is used to give movement
 * habilities to an object or other components
 * that needs to move based on elapsed time.
 * @version 0.1
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */
#pragma once

// - INCLUDES - //

// - DEFINES - //

// - CLASS - //

/**
 * @brief 
 * class which is used to give movement
 * habilities to an object or other components
 * that needs to move based on elapsed time.
 * This is sort of directly linked to
 * @ref Positions. Movements corresponds to
 * the distance that needs to be done
 * in a determined amount of time.
 */
class Movements
{
    private:
        int deltaX = 0;
        int deltaY = 0;
    public:

        /**
         * @brief Construct a new Mouvements object.
         * The initial velocity of the object isnt
         * specified but defaults to 0 on both the
         * X axis as well as the Y axis.
         * Movements corresponds to
         * the distance that needs to be done
         * in a determined amount of time.
         */
        Mouvements();

        /**
         * @brief
         * Allows you to simultaniously set both
         * X and Y velocities/deltas in a single
         * function. While you can use this to
         * set them back to 0, we recommend using
         * @ref ResetDeltas instead.
         * @param newDeltaX
         * The new velocity that the object should
         * have on the X horizontal axis.
         * @param newDeltaY
         * The new velocity that the object should
         * have on the Y vertical axis.
         * @return true:
         * Successfully set the new deltas.
         * @return false:
         * An error occured while attempting to
         * put the specified delta as movements.
         */
        bool SetDeltas(int newDeltaX, int newDeltaY);

        /**
         * @brief 
         * Gets the current velocity / delta on
         * the X axis. Movements corresponds to
         * the distance that needs to be done
         * in a determined amount of time.
         * @return int 
         */
        int DeltaX();

        /**
         * @brief 
         * Sets a new delta / velocity / movement
         * for the X axis that specifies how much
         * distance needs to be parkoured by the
         * object on the horizontal axis.
         * @param newDeltaX 
         * @return int 
         */
        int DeltaX(int newDeltaX);

        /**
         * @brief 
         * Gets the current velocity / delta on
         * the Y axis. Movements corresponds to
         * the distance that needs to be done
         * in a determined amount of time.
         * @return int 
         */
        int DeltaY();

        /**
         * @brief 
         * Sets a new delta / velocity / movement
         * for the Y axis that specifies how much
         * distance needs to be parkoured by the
         * object on the vertical axis.
         * @param newDeltaY 
         * @return int 
         */
        int DeltaY(int newDeltaY);

        /**
         * @brief 
         * Simply puts the velocities / deltas
         * back to 0 in a single function.
         * @return true:
         * The deltas were not at 0 and they
         * are now at 0.
         * @return false:
         * Both the deltas were already at 0. 
         */
        bool ResetDeltas();
};