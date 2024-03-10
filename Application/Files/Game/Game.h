/**
 * @file Game.h
 * @author LyamBRS
 * @brief 
 * Header file for the Game class which is used
 * to create a game with a map and 1 or more
 * players.
 * @version 0.1
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include <iostream>
#include <vector>
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../Controller/Controller.h"
#include "../PlacedBomb/PlacedBomb.h"
#include "../PlacedPowerUp/PlacedPowerUp.h"
#include "../SimpleTimer/SimpleTimer.h"
#include "../Movements/Movements.h"

// - DEFINES - //
#define EM_GAME_WRONG_AMOUNT_OF_PLAYERS "invalid specified amount of players"
#define EM_GAME_MAP_VALUE_WRONG_TYPE    "A map value is of the wrong type"
#define EM_GAME_MISSING_MAP_INFO   "Critical map info missing from JSON"
#define EM_GAME_UNDEFINED_ERROR    "UNDEFINED ERROR. PLEASE DEFINE"
#define EM_GAME_CORRUPTED_MAP      "The specified map is corrupted."
#define EM_GAME_NO_JSON_GIVEN      "No JSON was returned from the MAP obj"
#define EM_GAME_MAP_IS_NULLPTR     "The passed map is a nullptr        "
#define EM_GAME_TOO_MANY_PLAYERS   "There is too many players to play  "
#define EM_GAME_NOT_ENOUGH_PLAYERS "There is not enough players to play"

// - CLASS - //

/**
 * @brief 
 * # Game
 * @brief
 * The Game class allows you to create and start
 * a game based with X amount of players from a
 * map template saved at specified location on
 * the user's device. A game consists of a map,
 * some players, some bombs, some shenanigans.
 * A game goes on until either a player leaves
 * or or there is only one left.
 */
class Game
{
    private:
        /// @brief Holds the map loaded in the game.
        Map* map;
        /// @brief All the players currently playing.
        std::vector<Player*> players;
        /// @brief All the bombs that are currently on the map.
        std::vector<PlacedBomb*> bombsOnMap;
        /// @brief All the potential power ups on the map that a player can pick up.
        std::vector<PlacedPowerUp*> itemsOnMap;

        std::string errorMessage = "";

        /// @brief How long has the game been going for? (in milliseconds)
        int timeSinceStart = 0;
        /// @brief How long until the game starts and players can move
        SimpleTimer startTimer = SimpleTimer(3000);

        /// @brief Tells if the game is ready to be PLAYED
        bool gameIsReady = false;

        /// @brief Is set to true if the Game object is structurally ready to be used.
        bool canBeUsed = false;

        /// @brief Is set to true if the game should no longer update.
        bool isPaused = false;
        
        /**
         * @brief 
         * # DisplayMap
         * @brief
         * Actually prints the current map layout in a
         * command prompt or updates the QT application
         * with the current map layout.
         * @attention
         * THIS DOES NOT UPDATE THE MAP. IT ONLY PRINTS
         * IT / DISPLAYS IT
         * @return true:
         * Successfully displayed the map
         * @return false:
         * Whatever hapenned, there was an error.
         */
        bool DisplayMap();

        /**
         * @brief 
         * # HandleNextMouvements
         * @brief
         * This function is used to update players movement
         * on the map. This function takes their associatd
         * controllers and updates each player's movements
         * based on that. This function DOES NOT check for
         * walls or anything, it only handles the movements
         * of players. @ref HandlePlayers is used to do the
         * rest.
         * @return true:
         * Successfully updated all the player's next
         * movements.
         * @return false:
         * Failed to update the movements. 
         */
        bool HandleNextMouvements();

        /**
         * @brief 
         * # PutObjectsInMap
         * @brief
         * Takes all the object's current positions and
         * update the map so that their positions correspond
         * to an actual map place. This function does NOT
         * check if the position is valid or not. It is other
         * function that checks for that.
         * @return true:
         * All objects were placed on the map.
         * @return false:
         * Failed to put objects on the map.
         */
        bool PutObjectsInMap();

        /**
         * @brief 
         * # HandleBombs
         * @brief
         * Function that handles all the bombs.
         * This function defines where the smoke particles
         * need to be on the map, places bombs when players
         * want to, etc. In shorts... bombs are handled lmfao.
         * @return true:
         * Successfully handled all unidentified objects from
         * the middle east.
         * @return false:
         * Error occured while handling bombs. BOOM.
         */
        bool HandleBombs();

        /**
         * @brief 
         * # HandlePlayers
         * @brief
         * Handles all the players attributes and actions.
         * This function moves the players based on their
         * wanted movements, checks if their end positions
         * would make sense, check if they are vulnerable
         * or not etc etc. In short, it handles players.
         * @return true:
         * Successfully handled players
         * @return false:
         * Failed to handle players.
         */
        bool HandlePlayers();

        /**
         * @brief 
         * # HandlePowerUp
         * @brief
         * Handles all the power ups that are currently
         * on the map, ready to be picked up by players.
         * Well, it handles powerup really... Anything
         * you gotta do with them, just do them in here
         * or some shit.
         * @return true:
         * Successfully handled power ups
         * @return false:
         * Roh oh, failed to handle powerups.
         */
        bool HandlePowerUp();

        /**
         * @brief 
         * # CheckForPlayerDamage
         * @brief
         * Function that checks if players should take
         * damage based on where they currently are
         * standing on the map.
         * @return true:
         * Successfully checked for player damage.
         * @return false:
         * Huh, I guess it failed to do as advertised.
         */
        bool CheckForPlayerDamage();

        /**
         * @brief 
         * # SelfCheck
         * @brief
         * This function verifies the entirety of the Game
         * object, including its map and players. If false
         * is returned, it failed the test and the first
         * encountered error is written in @ref errorMessage
         * @return true:
         * Passed the test
         * @return false:
         * Failed the test 
         */
        bool SelfCheck();

    public:

        /**
         * @brief
         * # DO NOT USE THIS CONSTRUCTOR OUTSIDE OF CLASS MEMBER DEFINITIONS
         */
        Game();

        /**
         * @brief 
         * # Game
         * @brief
         * The Game class allows you to create and start
         * a game based with X amount of players from a
         * map template saved at specified location on
         * the user's device. A game consists of a map,
         * some players, some bombs, some shenanigans.
         * A game goes on until either a player leaves
         * or or there is only one left.
         * @param connectedPlayerCount
         * How many players should be on the map?
         * @param MapData
         * JSON file as an object which corresponds to the loaded
         * map that will be played on.
         */
        Game(int connectedPlayerCount, Map* MapData);

        /**
         * @brief 
         * Generic updater function. Must be called each
         * frames so that the game works. This function
         * handles EVERYTHING that should happen on a
         * frame to frame basis like player movements,
         * timers, bombs exploding, you name it!
         * @return true:
         * Successfully updated the game.
         * @return false:
         * Failed to update the game.
         */
        bool Update();

        /**
         * @brief 
         * Starts the game. When this is called, a 3 second
         * timer will ensue after which the game will start
         * and players will be able to move around and find
         * out.
         * @return true:
         * Successfully started the game
         * @return false:
         * Failed to start the game. Path problem?
         */
        bool Start();

        /**
         * @brief 
         * Updates a player's movements and actions based
         * on what their associated controller says.
         * If the controller is suddently offline, the
         * game will stop.
         * @param controllerToUpdate
         * Which controller should be used to move
         * the player?
         * @param associatedPlayer
         * Which player should this controller affect?
         * @return true:
         * Successfully updated the player's attributes
         * with the Controller's attributes
         * @return false:
         * Failed to put the controller into the player.
         */
        bool UpdateControllerAndPlayer(Controller* controllerToUpdate, int associatedPlayer);
};