/**
 * @file PlacedBomb.h
 * @author LyamBRS
 * @brief
 * Holds the header definition of the placebomb
 * object. Allowing bombs to be seen and interact
 * with the map.
 * @version 0.1
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */
#pragma once

// - INCLUDES - //
#include "../BaseObject/BaseObject.hpp"
#include "../SimpleTimer/SimpleTimer.h"

// - DEFINES - //

// - CLASS - //

/**
 * @brief 
 * This class allows bombs to be handled on
 * the map and in the game.
 * This allows a bomb with a set explosive
 * radius to be placed on the map at a
 * specified coordinate. You must specify the
 * explosive force (radius in blocks) and the
 * length of the fuse (how many updates until
 * it starts exploding)
 */
class PlacedBomb : public BaseObject
{
    private:

        /// @brief How long until the bomb starts exploding.
        SimpleTimer timeTillBoom = SimpleTimer(0);

        /// @brief The final explosion radius that the bomb will reach.
        int explosivePower = 0;

        /// @brief The current radius of the explosion. Starts at 0
        int currentExplosionRadius = 0;

        bool isExploding = false;

        bool isExploded = false;

    public:

        /**
         * @brief Construct a new Placed Bomb object.
         * This allows a bomb with a set explosive
         * radius to be placed on the map at a
         * specified coordinate. You must specify the
         * explosive force (radius in blocks) and the
         * length of the fuse (how many updates until
         * it starts exploding)
         * @param x
         * The position in the horizontal axis where
         * the bomb should be placed.
         * @param y
         * The position in the vertical axis where
         * the bomb should be placed.
         * @param explosiveForce
         * Radius of the final explosion.
         * @param fuseLength
         * How long until it actually detonates.
         */
        PlacedBomb(int x, int y, int explosiveForce, int fuseLength);

        /**
         * @brief 
         * Updates the bomb object. This allows the
         * object to update its sprite and its timers
         * The bomb will firstly count down then it
         * will explode until it reaches its maximum
         * radius after which it will stay that size
         * for a couple more updates until its done
         * animating.
         * @return true:
         * Successfully updated the placed bomb
         * @return false:
         * Failed to update the bomb. The bomb is
         * finished exploding.
         */
        bool Update();

        /**
         * @brief 
         * Tells you if the bomb has finished fully
         * exploding. You then must delete this object.
         * @return true:
         * The bomb is done doing bomb shit.
         * @return false:
         * Bomb still doing bomb shit.
         */
        bool HasFinishedExploding();

        // Fuck you C++ inheritance. Wasted 2h on your ass for jack shit.
        Movements* GetVelocity();

        Positions* GetCurrentCoordinates();

        Positions* GetOldCoordinates();
};