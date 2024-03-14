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
#include "../BaseObject/BaseObject.hpp"
#include "../Controller/Controller.h"
#include "../PowerUp/PowerUp.h"
#include "../Colour/Colour.h"
#include "../SimpleTimer/SimpleTimer.h"
#include "../Inventory/Inventory.h"
#include <windows.h>

// - DEFINES - //
#define PLAYER_FULL_HEALTH 100
#define PLAYER_BASE_BOMB_PLACEMENT_TIMER 2000
#define boutonBombe 1

#define PLAYER_A_COLOR colors::electric
#define PLAYER_B_COLOR colors::yellow
#define PLAYER_C_COLOR colors::leaf
#define PLAYER_D_COLOR colors::aqua

#define PLAYER_KEY_SELECT       joystickButton
#define PLAYER_KEY_Y_AXIS       joystickX
#define PLAYER_KEY_X_AXIS       joystickY
#define PLAYER_KEY_INV_LEFT     leftButton
#define PLAYER_KEY_INV_RIGHT    rightButton
#define PLAYER_KEY_USE_PWR      topButton
#define PLAYER_KEY_DISCARD_PWR  bottomButton

#define PLAYER_LOCAL_SELECT       controllerRef->PLAYER_CONTROLLER_SELECT
#define PLAYER_LOCAL_Y_AXIS       controllerRef->PLAYER_CONTROLLER_Y_AXIS
#define PLAYER_LOCAL_X_AXIS       controllerRef->PLAYER_CONTROLLER_X_AXIS
#define PLAYER_LOCAL_INV_LEFT     controllerRef->PLAYER_CONTROLLER_INV_LEFT
#define PLAYER_LOCAL_INV_RIGHT    controllerRef->PLAYER_CONTROLLER_INV_RIGHT
#define PLAYER_LOCAL_USE_PWR      controllerRef->PLAYER_CONTROLLER_USE_PWR
#define PLAYER_LOCAL_DISCARD_PWR  controllerRef->PLAYER_CONTROLLER_DISCARD_PWR

#define PLAYER_CONTROLLER_THRESHOLD 30

// - FUNCTION - //
int GetPlayerColor(unsigned int playerNumber);

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
class Player : BaseObject
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

        /// @brief Linked to a real controller.
        Controller* controllerRef = new Controller();

        SimpleTimer bombPlacement = SimpleTimer(3000);
        Inventory inventaire;

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
        Player(int initialX, int initialY, std::string wantedAscii, int wantedColour);

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

        bool LinkController(Controller* newControllerReference);
        bool UnlinkController();
        Controller* GetController();

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
         * @return true:
         * Successfully updated the player's attributes
         * based on the referenced controller. 
         * @return false:
         * Failed to update the player's attributes.
         */
        bool UpdateFromController();

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

        void addPowerUp(PowerUp* powerUp);

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

        /**
         * @brief 
         * Tells if that specific player's controller is currently
         * connected or not.
         * @return true:
         * Is connected
         * @return false:
         * Is not connected 
         */
        bool IsConnected();
};