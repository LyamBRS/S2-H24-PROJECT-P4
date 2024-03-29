/**
 * @file PlacedPowerUp.h
 * @author LyamBRS
 * @brief
 * header definition for the object based
 * @ref PlacedPowerUp class allowing power
 * ups to be placed physically on the map
 * for players to pick them up.
 * @version 0.1
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include <iostream>
#include "../BaseObject/BaseObject.hpp"
#include "../SimpleTimer/SimpleTimer.h"
#include "../PowerUp/PowerUp.h"
// - DEFINES - //
#define POWERUP_DESPAWN_TIMER_VALUE 5000

// - CLASS - //

/**
 * @brief
 * # PlacedPowerUp
 * @brief
 * defines a @ref PowerUp on the @ref Map which can
 * be picked up by @ref Players when their @ref
 * Position match that of this object. This object
 * is then converted to an @ref Item held by the
 * @ref Player's @ref Inventory after which they
 * can select it by using their associated @ref
 * Controller as they play the @ref Game.
 */
class PlacedPowerUp : public BaseObject
{
    private:
        /// @brief Which type of PowerUp is it?
        int type = 0;
        /// @brief How long until it despawns because no players picked it up?
        SimpleTimer* Timetilldespawn = new SimpleTimer(POWERUP_DESPAWN_TIMER_VALUE);
        bool shoulbedeleted=0;
    public:
        /**
         * @brief
         * # PlacedPowerUp
         * @brief
         * Constructs an object that defines a @ref PowerUp
         * on the @ref Map which can be picked up by
         * @ref Players when their @ref Position match that
         * of this object. This object is then converted to
         * an @ref Item held by the @ref Player's 
         * @ref Inventory after which they can select it by
         * using their associated @ref Controller as they
         * play the @ref Game
         * @param x
         * Where should this powerup be on the @ref Map?
         * @param y
         * Where should this powerup be on the @ref Map?
         * @param type
         * Which type of @ref PowerUp is this?
         */
        PlacedPowerUp(int initialX, int initialY, int newType);

        /**
         * @brief
         * # Update
         * @brief 
         * Updates the PlacedPowerUp. Decreases timers,
         * change sprites and colours... Do whatever a
         * PlacedPowerUp does each frame.
         * @return true:
         * Successfully updated the object.
         * @return false:
         * Failed to update the object.
         */
        bool Update();

        /**
         * @brief 
         * # ShouldBeDeleted
         * @brief 
         * Method that tells you if this PlacedPowerUp
         * needs to be deleted because it has exeeded its
         * time on the @ref Map without any @ref Player
         * ever picking it up for themselves.
         * @return true:
         * PowerUp needs to be removed from the map.
         * @return false:
         * Nah, it should stay
         */
        bool ShouldBeDeleted();

        int GetType();

        // Fuck you C++ inheritance. Wasted 2h on your ass for jack shit.
        Movements* GetVelocity();

        Positions* GetCurrentCoordinates();

        Positions* GetOldCoordinates();
};