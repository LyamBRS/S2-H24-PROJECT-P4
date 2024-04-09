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
#include "../Map/Utils.hpp"
#include "../Player/Player.h"
#include "../Controller/Controller.h"
#include "../PlacedBomb/PlacedBomb.h"
#include "../PlacedPowerUp/PlacedPowerUp.h"
#include "../SimpleTimer/SimpleTimer.h"
#include "../Movements/Movements.h"
#include "../Application/AppHandler.h"
#include "../Colour/Colour.h"
#include "../SimpleTimer/SimpleChrono.h"
#include "../PlacedBomb/PlacedBomb.h"
#include <random>

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

#define GAME_MIN_WIDTH 30
#define GAME_HEADER_HEIGHT 5

#define GAME_WINDOW_BORDER_BG colors::lightred
#define GAME_WINDOW_BORDER_FG colors::darkpurple
#define GAME_WINDOW_BORDER_CHAR CHAR_CONTRAST_HIGH
#define GAME_BORDER GAME_WINDOW_BORDER_CHAR,GAME_WINDOW_BORDER_FG,GAME_WINDOW_BORDER_BG

#define GAME_WINDOW_BACKGROUND_BG colors::white
#define GAME_WINDOW_BACKGROUND_FG colors::black
#define GAME_WINDOW_BACKGROUND_CHAR ' '
#define GAME_BACKGROUND GAME_WINDOW_BACKGROUND_CHAR,GAME_WINDOW_BACKGROUND_FG,GAME_WINDOW_BACKGROUND_BG

#define GAME_WINDOW_DIVIDER_BG colors::white
#define GAME_WINDOW_DIVIDER_FG colors::darkpurple
#define GAME_DIVIDER_COLORS GAME_WINDOW_DIVIDER_FG, GAME_WINDOW_DIVIDER_BG

#define GAME_DIVIDER_TL_CORNER CHAR_BORDER_TL_CORNER, GAME_DIVIDER_COLORS
#define GAME_DIVIDER_BL_CORNER CHAR_BORDER_BL_CORNER, GAME_DIVIDER_COLORS 
#define GAME_DIVIDER_TR_CORNER CHAR_BORDER_TR_CORNER, GAME_DIVIDER_COLORS
#define GAME_DIVIDER_BR_CORNER CHAR_BORDER_BR_CORNER, GAME_DIVIDER_COLORS

#define GAME_DIVIDER_HORIZONTAL CHAR_BORDER_HORIZONTAL, GAME_DIVIDER_COLORS
#define GAME_DIVIDER_VERTICAL   CHAR_BORDER_VERTICAL, GAME_DIVIDER_COLORS
#define GAME_DIVIDER_T_JUNCTION CHAR_BORDER_T_JUNCTION, GAME_DIVIDER_COLORS
#define GAME_DIVIDER_B_JUNCTION CHAR_BORDER_B_JUNCTION, GAME_DIVIDER_COLORS
#define GAME_DIVIDER_L_JUNCTION CHAR_BORDER_L_JUNCTION, GAME_DIVIDER_COLORS
#define GAME_DIVIDER_R_JUNCTION CHAR_BORDER_R_JUNCTION, GAME_DIVIDER_COLORS


#define GAME_WINDOW_FIELD_BG colors::grey
#define GAME_WINDOW_FIELD_FG colors::lightgrey
#define GAME_FIELD_COLORS GAME_WINDOW_FIELD_FG, GAME_WINDOW_FIELD_BG
#define GAME_FIELD ' ', GAME_WINDOW_FIELD_FG, GAME_WINDOW_FIELD_BG

#define GAME_FIELD_WIDTH_TIMER 8
#define GAME_FIELD_WIDTH_COOLDOWN 3
#define GAME_FIELD_WIDTH_PLAYER_NAME 9
#define GAME_FIELD_WIDTH_BOMB_STATUS 1
#define GAME_FIELD_WIDTH_HEALTH 4
#define GAME_FIELD_WIDTH_INVENTORY 5

#define GAME_CURSOR_GAME_MESSAGE 1
#define GAME_CURSOR_GAMETIMER_Y 3
#define GAME_CURSOR_MAP_Y 6

#define GAME_BOMB_UPDATE_DELAY_MS 50
#define GAME_DEFAULT_BOMB_RADIUS 8
#define GAME_DEFAULT_DAMAGE 1

#define TER std::cout

// - STRUCT - //
/**
 * @brief 
 * # GameStatuses
 * @brief 
 * This struct holds all the possible statuses and their meanings
 * that a @ref Game object can hold. The @ref Game status is
 * obtained through Game.GetStatus().
 * @brief
 * - 0: Invalid game. Corruption detected / constructor error
 * @brief
 * - 1: Game is waiting for all players to confirm that they are ready
 * @brief
 * - 2: Game is doing a countdown
 * @brief
 * - 3: Game is actively being played
 * @brief
 * - 4: Game is paused, and the pause menu is shown.
 * @brief
 * - 5: Game has ended.
 * @brief
 * - 6: Waiting for player to reconnect
 */
enum GameStatuses
{
    invalid = 0,
    awaitingPlayers = 1,
    countdown = 2,
    playing = 3,
    paused = 4,
    ended = 5,
    awaitingConnection = 6
};

// - CLASS - //

/**
 * @brief 
 * # BomberManGame
 * @brief
 * The Game class allows you to create and start
 * a game based with X amount of players from a
 * map template saved at specified location on
 * the user's device. A game consists of a map,
 * some players, some bombs, some shenanigans.
 * A game goes on until either a player leaves
 * or or there is only one left.
 */
class BomberManGame
{
    private:
        /// @brief Holds the map loaded in the game.
        Map* map;
        /// @brief All the players currently playing.
        std::vector<Player> players;
        /// @brief All the bombs that are currently on the map.
        std::vector<PlacedBomb> bombsOnMap;
        /// @brief All the potential power ups on the map that a player can pick up.
        std::vector<PlacedPowerUp> itemsOnMap;

        std::string errorMessage = "";
        std::string gameMessage = "";

        /// @brief How long has the game been going for? (in milliseconds)
        int timeSinceStart = 0;
        /// @brief How long until the game starts and players can move
        SimpleTimer startTimer = SimpleTimer(4000);
        SimpleTimer handlerTimer = SimpleTimer(1);
        SimpleChrono gameDuration = SimpleChrono();
        SimpleTimer bombUpdateTimer = SimpleTimer(GAME_BOMB_UPDATE_DELAY_MS);

        bool statusChanged = false;

        int gameStatus = 0;
        int gameWidth = 0;
        int gameHeight = 0;

        int playerCardStartY = 0;
        int gameTimerOffset = 0;
        int playerCardOffsetX = 0;
        int firstPlayerCardY = 0;
        int messageCursorY = 0;
        
        int cooldownCursorX = 0;
        int bombStatusCursorX = 0;
        int healthCursorX = 0;
        int inventoryCursorX = 0;

        int mapCursorX = 0;
        int mapCursorY = 0;

        int gameTimerCursorX = 0;

        /// @brief Is set to true if the Game object is structurally ready to be used.
        bool canBeUsed = false;

        /// @brief reference to the attributes of the current application
        AppHandler* appRef;

        bool needToRedrawMap = true;
        bool needToRedrawInventories = true;
        bool needToRedrawPlayerStatus = true;
        bool needToRedrawTimers = true;
        bool needToRedrawPlayerHealth = true;
        bool needToRedrawMessage = true;

        SimpleTimer drawingFlipper = SimpleTimer(200);
        SimpleTimer playerDeathMessage = SimpleTimer(2000);
        SimpleTimer gameMessageReset = SimpleTimer(2000);
        bool flipDrawingOrder = false;
        
        /**
         * @brief 
         * # DrawMap
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
        bool DrawMap();
        bool DrawGameHeader();
        bool DrawInventories();
        bool DrawPlayerStatus();
        bool DrawHealths();
        bool DrawTimers();
        bool DrawCooldowns();
        bool DrawMessages();

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
        bool PutPlayersInMap();
        bool PutBombsInMap();
        bool PutPowerUpsInMap();

        bool HandleBoxDestruction(Positions boxPosition);

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

        bool SetGameMessage(std::string newMessage);

    public:

        /**
         * @brief
         * # DO NOT USE THIS CONSTRUCTOR OUTSIDE OF CLASS MEMBER DEFINITIONS
         */
        BomberManGame();

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
         * @param newAppRef
         * Reference to the application. Usually given by menus.
         * @param MapData
         * JSON file as an object which corresponds to the loaded
         * map that will be played on.
         */
        BomberManGame(AppHandler* newAppRef, Map* MapData);

        /**
         * @brief 
         * Returns true if the Game is valid and ready to go and be played.
         * To be valid, the game must have been constructed through the right
         * constructor (once which specifies a @ref Map and an @ref Application reference).
         * @return true 
         * @return false 
         */
        bool isValidated();

        /**
         * @brief
         * # GetStatus
         * @brief
         * Returns the current state of the game as a number.
         * The number represents one of the followings:

         * @return int 
         */
        int GetStatus();

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
         * Pauses the game. This changes the status of the
         * game according to @ref GameStatuses allowing
         * it to freeze in time until it is @ref Resumed.
         * @return true:
         * Game was paused successfully
         * @return false:
         * Game is not started / already paused / invalid. 
         */
        bool Pause();

        /**
         * @brief 
         * Resumes the game. This changes the status of the
         * game according to @ref GameStatuses allowing
         * it to resume where it was in the gameplay.
         * @warning
         * ### This DOES NOT start a game.
         * @return true:
         * Game was paused successfully
         * @return false:
         * Game is not paused / already going / invalid. 
         */
        bool Resume();

        /**
         * @brief
         * # GetCountdownValue
         * @brief
         * Returns a number associated with the current countdown number value
         * Values are as followed:
         * @brief
         * - 0: No countdown in progress
         * @brief
         * - 1: GO
         * @brief
         * - 2: 1 second
         * @brief
         * - 3: 2 seconds
         * @brief
         * - 4: 3 seconds
         * @return int 
         */
        int GetCountdownValue();

        /**
         * @brief
         * # GetMap
         * @brief
         * Returns the map used inside of the @ref Game object.
         * Its that simple.
         * @return Map* 
         */
        Map* GetMap();

        /**
         * @brief 
         * # NeedsRedrawing
         * @brief
         * Used by menus to verify if the game actually requires
         * to be re-drawn on the terminal or not. This is done to
         * avoid having to constantly update the terminal at frame
         * speeds if nothing needs to be actually drawn and the
         * old displayed characters are all still relevant.
         * @attention
         * The Game needs to be drawn in a @ref Menu, by calling its
         * @ref Draw() method. You can choose to ignore this method
         * and redraw the @ref Game anyways, but doing so too fast
         * will cause terminal artifacts.
         * @warning
         * YOU MUST use @ref FreshDraw() if the terminal was previously
         * used for other purposes than SOLELY drawing the @ref Game.
         * @return true:
         * The @ref Game has changed, and drawing needs to occur.
         * @return false:
         * The @ref Game has not changed, no drawing is needed.
         */
        bool NeedsRedrawing();

        /**
         * @brief 
         * # Draw
         * @brief
         * The Draw method allows a @ref Menu to print the current
         * @ref Game in the active terminal window. This method will
         * print player's statuses, @ref Inventories, as well as the
         * @ref Map used in this @ref Game object.
         * @attention
         * This method WILL NOT print THE ENTIRE @ref Game. It only
         * prints parts that changed since the last call of the
         * method and that thus, needs to be updated on the screen.
         * To draw the ENTIRE @ref Game in your terminal window, you
         * must use the @ref FreshRedraw method.
         * @return true:
         * Successfully drew the game in the std::cout terminal.
         * @return false:
         * Failed to draw in std::cout / No drawing were necessary.
         */
        bool Draw();

        /**
         * @brief 
         * # FreshDraw
         * @brief
         * A complete and extensive @ref Draw method. This method will
         * re-print the complete @ref Game, along with the aesthetics
         * that only needs to be printed once. This can be very demanding
         * for large maps and large amount of player counts.
         * @attention
         * To optimize your drawing speeds and help reduce terminal
         * artifacts, please only call this method when absolutely
         * necessary, like when the terminal was previously used for other
         * drawing purposes and its the first @ref Game frame. To do this
         * use methods such as @ref Draw and @ref NeedsRedrawing.
         * @return true:
         * Successfully printed the @ref Game to the terminal using std::cout.
         * @return false:
         * Failed to print to std::cout / Game is not instanciated properly.
         */
        bool FreshDraw();

        /**
         * @brief 
         * # AssignControllerToPlayer
         * @brief
         * Allows the program to assign a specific @ref Controller to a specific
         * @ref Player. This is done when the game's status 
         * is @ref GameStatuses::awaitingPlayers. Once a @ref Controller is assigned, 
         * it cannot be assigned to another @ref Player. 
         * @param controllerToUse 
         * @param playerIndex 
         * @return true 
         * @return false 
         */
        bool AssignControllerToPlayer(Controller* controllerToUse, int playerIndex);

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

        Controller* GetPlayerController(int playerIndex);
        bool AssignControllerToPlayer(int playerIndex, Controller* controllerRef);
        bool UnAssignPlayerController(int playerIndex);

        int GetWinningPlayerID();

        bool UsePowerUp(int playerID, int powerUpID);
};