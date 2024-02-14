/**
 * @file PowerUp.h
 * @author LyamBRS
 * @brief
 * Contains the header definition of the PowerUp
 * class. The PowerUp class allows powerups to be
 * stored in an inventory as well as store their
 * sprites and actions.
 * @version 0.1
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include <iostream>
#include "../PlacedPowerUp/PlacedPowerUp.h"

// - DEFINES - //

// - CLASS - //
class PowerUp
{
    private:
        /// @brief The name of this powerup.
        std::string name = "UNDEFINED";
        /// @brief A short description of the habilities given from using this powerup.
        std::string description = "UNDEFINED";
        /// @brief The type of this power up.
        int type = 0;

    public:
        /**
         * @brief 
         * # PowerUp
         * @brief 
         * Construct a new Power Up object.
         * A Power Up allows @ref Players to use special
         * habilities whenever they want during the
         * @ref Game. Power ups are created from Power
         * ups that lays around on the @ref Map which are
         * ready to be picked up, @ref PlacedPowerUp.
         * @param powerUpToPickUp
         * Which power up on the @ref Map should this
         * @ref Inventory based power up be created
         * from?
         */
        PowerUp(PlacedPowerUp* powerUpToPickUp);
};
