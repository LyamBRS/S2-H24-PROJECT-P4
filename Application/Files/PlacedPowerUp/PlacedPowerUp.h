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
#include "../PowerUp/PowerUp.hpp"

// - DEFINES - //
#define POWERUP_DESPAWN_TIMER_VALUE 10000

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
        int timeTillDespawn = POWERUP_DESPAWN_TIMER_VALUE;

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
        PlacedPowerUp(int initialX, int initialY, int type);

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
};