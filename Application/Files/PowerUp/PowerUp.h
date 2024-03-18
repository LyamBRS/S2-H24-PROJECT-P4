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
/**
 * @brief
 * # PowerUpID
 * @brief
 * Holds the ID of each potential power up that
 * you can obtain in the game. There is 16
 * potential power up that can be in the game.
 * This limitation comes from the way the @ref Map
 * BinaryTiles works. This is the most efficient
 * way I could come up with to store data in each
 * tiles on the map.
 */
enum PowerUpID
{
    damage_increase = 0b0000'0000'0000'0000,
    speed_increase = 0b0001'0000'0000'0000,
    explosion_radius_increase = 0b0010'0000'0000'0000,
    health_increase = 0b0011'0000'0000'0000,
    nb_bomb_increase = 0b0100'0000'0000'0000,
    powerUpFName = 0b0101'0000'0000'0000,
    powerUpGName = 0b0111'0000'0000'0000,
    powerUpHName = 0b1000'0000'0000'0000,
    powerUpIName = 0b1001'0000'0000'0000,
    powerUpJName = 0b1010'0000'0000'0000,
    powerUpKName = 0b1011'0000'0000'0000,
    powerUpLName = 0b1100'0000'0000'0000,
    powerUpMName = 0b1101'0000'0000'0000,
    powerUpNName = 0b1111'0000'0000'0000
};

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
        
        /**
         * @brief 
         * return the binary number from PowerUpID
         * Uses the type from PlacedPowerUP
         */
        unsigned int getPowerUpValue(int type);

        
        std::string getDescription();
        void setDescription(std::string nom);

        int getType();

};
