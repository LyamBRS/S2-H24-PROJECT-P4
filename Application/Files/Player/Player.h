/**
 * @file Player.h
 * @author LyamBRS
 * @brief
 * Header file used for the player's
 * class. Player class shenanigans
 * amogus sussy balls.
 * See @ref Player for a better
 * description.
 * @version 0.1
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */
#pragma once

// - INCLUDES - //
#include <iostream>
#include "../Object/Object.hpp"
#include "../Controller/Controller.h"
#include "../PowerUp/PowerUp.h"

// - DEFINES - //
#define PLAYER_FULL_HEALTH 100
#define PLAYER_BASE_BOMB_PLACEMENT_TIMER 2000
// - CLASS - //

/**
 * @brief
 * # Player
 * @brief
 * The player class builds the different players
 * that are playing in a game. Each player inherits
 * from @ref Object making it able to have a
 * position on the map, 2D velocities as well as
 * basic screen attributes so that they can each
 * have their own colours and ascii representation
 * on the screen.
 */
class Player : public Object
{
    private:
        /// @brief How much more until this bastards die? 0-100
        int health = PLAYER_FULL_HEALTH;
        /// @brief Time left until the player starts getting affected by damage again.
        int invulnerabilityTimer = 0;
        /// @brief Time left until the player can place another boom stick
        int bombPlacementTimer = PLAYER_BASE_BOMB_PLACEMENT_TIMER;
        /// @brief Tells if the player wants to place a bomb. @ref PlacedABomb is used globally.
        bool wantsToPlaceBomb = false;
        /// @brief Tells if the player wants to use item he has currently selected.
        bool wantsToUseSelectedItem = false;
        /// @brief Simply says if the player is alive rn or not.
        bool isAlive = true;

    public:

        /**
         * @brief
         * # Player
         * @brief
         * The player class builds the different players
         * that are playing in a game. Each player inherits
         * from @ref Object making it able to have a
         * position on the map, 2D velocities as well as
         * basic screen attributes so that they can each
         * have their own colours and ascii representation
         * on the screen.
         * @param initialX
         * Where should the player initially be on the map?
         * @param initialY
         * Where should the player initially be on the map?
         * @param wantedAscii
         * What should be used to represent the player?
         * @param wantdColour
         * What colour should the player be?
         */
        Player(int initialX, int initialY, std::string wantedAscii, char wantdColour);

        /**
         * @brief
         * # PlacedABomb
         * @brief
         * Tells you if the player has pressed a button to
         * place a bomb. This is only real if the player's
         * counter to place bomb is available.
         * @return true:
         * The player NEEDS to place a bomb next frame
         * @return false:
         * The player SHOULDN'T place a bomb on the next frame.
         */
        bool PlacedABomb();

        /**
         * @brief
         * # Health
         * @brief
         * Tells you how much health that player has.
         * The value ranges from 0 to 100 and defaults
         * at 100. You can use @ref GiveDamage to
         * remove health from the player as well as
         * @ref GiveHealth to give health back to a
         * player.
         * @return int 
         */
        int Health();

        /**
         * @brief 
         * # GiveHealth
         * @brief 
         * Gives a certain amount of health to the player.
         * Certain powerups could give the player more
         * health. However, the starting maximum health
         * that a player can have is 100. Any value above
         * that number won't add shit.
         * @attention
         * This gives X more health to the player. This
         * does NOT set the player health to that number.
         * @param healthPoint
         * How much health should the player get?
         * @return true:
         * Successfully gave the player health
         * @return false:
         * Failed to give the player health. Already at
         * max capacity or whatever.
         */
        bool GiveHealth(int healthPoint);

        /**
         * @brief
         * # GiveDamage
         * @brief
         * Used to remove health from a player. The player
         * will then enter an invulnerability phase where
         * they will NOT loose health. 
         * @param damagePoints
         * How much health should be taken away from
         * the player?
         * @return true
         * Successfully took that amount out of their health. 
         * @return false:
         * The player cant take damages at the moment.
         */
        bool GiveDamage(int damagePoints);

        /**
         * @brief
         * # UpdateFromController
         * @brief
         * takes a specified controller and applies its
         * various inputs into actions that the player
         * can do. Such as update its movements, place
         * a bomb, change the selected item, use the
         * selected item etc.
         * @attention
         * ## THIS DON'T CHANGE PLAYER'S POSITIONS. aight?
         * @param controller
         * Reference to the controller associated with the
         * plyer.
         * @return true:
         * Successfully updated the player's attributes
         * based on the referenced controller. 
         * @return false:
         * Failed to update the player's attributes.
         */
        bool UpdateFromController(Controller* controller);

        /**
         * @brief
         * # GetActivatedPowerUp
         * @brief
         * Returns a reference to the @ref PowerUp that the
         * player has currently selected AND wants to use.
         * This is used so that the powerup can be applied
         * in the game's space and later removed from their
         * inventory if needs be.
         * @warning
         * If the player DOES NOT want to use that powerup,
         * @ref nullptr is returned. BE CAREFUL.
         * @return PowerUp* 
         */
        PowerUp* GetActivatedPowerUp();

        /**
         * @brief
         * # RemoveSelectedPowerUp
         * @brief
         * Removes the currently selected @ref PowerUp from
         * the player's inventory. They will no longer be
         * able to see that @ref PowerUp nor use it.
         * @return true:
         * Successfully removed the power up.
         * @return false:
         * Failed to remove the power up.
         */
        bool RemoveSelectedPowerUp();
};