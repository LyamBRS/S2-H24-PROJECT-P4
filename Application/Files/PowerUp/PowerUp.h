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
#include <map>

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
    nil = 0,
    damage_increase = 1,
    speed_increase = 2,
    explosion_radius_increase = 3,
    health_increase = 4,
    nb_bomb_increase = 5,
    deployableWall = 6,
    bombWall = 7,
    powerUpHName = 8,
    powerUpIName = 9,
    powerUpJName = 10,
    powerUpKName = 11,
    powerUpLName = 12,
    powerUpMName = 13,
    powerUpNName = 14
};

struct PowerUpNames
{
    std::string nil                         = "UNDEFINED";
    std::string damage_increase             = "DAMAGE INCREASE";
    std::string speed_increase              = "SPEED INCREASE";
    std::string explosion_radius_increase   = "EXPLOSION RADIUS";
    std::string health_increase             = "HEALTH PACK";
    std::string nb_bomb_increase            = "MORE BOMBS";
    std::string deployableWall              = "DEPLOYABLE WALL";
    std::string bombWall                    = "BOMB OF WALLS";
    std::string powerUpHName                = "RESERVED";
    std::string powerUpIName                = "RESERVED";
    std::string powerUpJName                = "RESERVED";
    std::string powerUpKName                = "RESERVED";
    std::string powerUpLName                = "RESERVED";
    std::string powerUpMName                = "RESERVED";
    std::string powerUpNName                = "RESERVED";
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
        int useLeft = 0;

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
        PowerUp(int powerUpID, int amountOfUses);
        
        /**
         * @brief 
         * return the binary number from PowerUpID
         * Uses the type from PlacedPowerUP
         */
        unsigned int getPowerUpValue(int type);

        
        std::string getDescription();
        void setDescription(std::string nom);

        int getType();

        bool Use();
        int GetUsesLeft();
        bool IsDrained();
};

std::string GetPowerUpName(int ID);

bool IsStorable(int ID);
