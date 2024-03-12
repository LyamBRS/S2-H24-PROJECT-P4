/**
 * @file Game.cpp
 * @author LyamBRS
 * @brief
 * Contains the program executed to make the
 * Game class work.
 * @version 0.1
 * @date 2024-02-14
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "Game.h"

// - PROGRAM - //

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
bool Game::SelfCheck()
{
    // Check if there is any maps in the Game object
    if(map == nullptr)
    {
        errorMessage = EM_GAME_MAP_IS_NULLPTR;
        return false;
    }

    errorMessage = GetMapJsonError(map->GetCurrentMap());
    if(errorMessage != EM_MAP_NO_ERROR)
    {
        return false;
    }

    return true;
}

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
bool Game::DrawMap()
{
    return map->Draw();
}

bool Game::DrawGameHeader()
{
    ConsecutiveChar(TER, GAME_BORDER, gameWidth, true);

    // Math to put the text in the middle of the screen.
    nlohmann::json mapJSON = map->GetCurrentMap();
    std::string mapName = mapJSON["name"];
    int seperationBetweenTextAndBorder = ((gameWidth-2)-mapName.length())/2;

    ConsecutiveChar(TER, GAME_BORDER, 1, false);
    ConsecutiveChar(TER, GAME_BACKGROUND, seperationBetweenTextAndBorder, false);

    // Cant really center a name that isnt odd can you
    if(mapName.length()%2 != 0)
    {
        ConsecutiveChar(TER, GAME_BACKGROUND, 1, false);
    }

    PrintInColour(TER, mapName, GAME_WINDOW_BACKGROUND_FG, GAME_WINDOW_BACKGROUND_BG);
    ConsecutiveChar(TER, GAME_BACKGROUND, seperationBetweenTextAndBorder, false);
    return false;
}

bool Game::DrawInventories()
{
    return false;
}

bool Game::DrawPlayerStatus()
{
    return false;
}

bool Game::DrawTimers()
{
    return false;
}

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
bool Game::HandleNextMouvements()
{
    return false;
}

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
bool Game::PutObjectsInMap()
{
    return false;
}

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
bool Game::HandleBombs()
{
    return false;
}

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
bool Game::HandlePlayers()
{
    return false;
}

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
bool Game::HandlePowerUp()
{
    return false;
}

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
bool Game::CheckForPlayerDamage()
{
    return false;
}

/**
 * @brief
 * # DO NOT USE THIS CONSTRUCTOR TERSIDE OF CLASS MEMBER DEFINITIONS
 */
Game::Game()
{
    canBeUsed = false;
    gameStatus = GameStatuses::invalid;
}

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
Game::Game(AppHandler* newAppRef, Map* MapData)
{
    map = MapData;
    appRef = newAppRef;

    if(!SelfCheck())
    {
        std::cerr << "GAME: Self check failure" << std::endl;
        Sleep(1000);

        canBeUsed = false;
        gameStatus = GameStatuses::invalid;
        return;
    }

    // here we calculate the height in ascii chars necessary to draw the whole game, and more importantly, the width.
    int mapSizeX = map->GetCurrentMap()["sizeX"];
    gameWidth = mapSizeX*3;
    if(gameWidth < GAME_MIN_WIDTH)
    {
        gameWidth = GAME_MIN_WIDTH;
    }

    canBeUsed = true;
    gameStatus = GameStatuses::awaitingPlayers;
}

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
bool Game::Update()
{
    return false;
}

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
bool Game::Start()
{
    startTimer.Reset();
    gameStatus = GameStatuses::countdown;
    return true;
}

/**
 * @brief
 * # GetStatus
 * @brief
 * Returns the current state of the game as a number.
 * The number represents one of the followings:
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
 * @return int 
 */
int Game::GetStatus()
{
    return gameStatus;
}

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
int Game::GetCountdownValue()
{
    if(!canBeUsed) return 0;

    int timeLeft = startTimer.TimeLeft();

    if(gameStatus != GameStatuses::countdown)
    {
        return 0;
    }

    if(timeLeft > 3000)
    {
        return 4;
    }

    if(timeLeft > 2000)
    {
        return 3;
    }

    if(timeLeft > 1000)
    {
        return 2;
    }

    // The end of the timer was eventually reached as we attempted to read it. The game must then start.
    if(timeLeft == 0)
    {
        gameStatus = GameStatuses::playing;
    }

    return 1;
}

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
bool Game::UpdateControllerAndPlayer(Controller* controllerToUpdate, int associatedPlayer)
{
    return false;
}

/**
 * @brief
 * # GetMap
 * @brief
 * Returns the map used inside of the @ref Game object.
 * Its that simple.
 * @return Map* 
 */
Map* Game::GetMap()
{
    return map;
}

/**
 * @brief 
 * Returns true if the Game is valid and ready to go and be played.
 * To be valid, the game must have been constructed through the right
 * constructor (once which specifies a @ref Map and an @ref Application reference).
 * @return true 
 * @return false 
 */
bool Game::isValidated()
{
    return canBeUsed;
}













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
bool Game::NeedsRedrawing()
{
    if(!canBeUsed) return false;
    return needToRedrawInventories || needToRedrawMap || needToRedrawPlayerStatus || needToRedrawTimers;
}

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
bool Game::Draw()
{
    if(!canBeUsed) return false;

    if(needToRedrawMap)
    {
        needToRedrawMap = false;
        DrawMap();
    }

    if(needToRedrawTimers)
    {
        needToRedrawTimers = false;
        DrawTimers();
    }

    if(needToRedrawInventories)
    {
        needToRedrawInventories = false;
        DrawInventories();
    }

    if(needToRedrawPlayerStatus)
    {
        needToRedrawPlayerStatus = false;
        DrawPlayerStatus();
    }

    return true;
}

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
bool Game::FreshDraw()
{
    if(!canBeUsed) return false;

    //###################################################
    //# MATH DONE FOR VARIOUS PLACEMENTS AND CENTERINGS #
    //###################################################

    // Math to put the text in the middle of the screen.
    nlohmann::json mapJSON = map->GetCurrentMap();
    std::string mapName = mapJSON["name"];

    int seperationBetweenTextAndBorder = ((gameWidth-2)-mapName.length())/2;
    // Cant really center a name that isnt odd can you
    if(mapName.length()%2 != 0)
    {
        ConsecutiveChar(TER, GAME_BACKGROUND, 1, false);
    }

    int seperationBetweenGameTimer = ((gameWidth-4) - GAME_FIELD_WIDTH_TIMER)/2;  // Centers the timer. -4 because of dividers next to it.

    //###############################################################
    //# TOP PORTION OF THE GAME, DRAW THE NAME OF THE MAP, CENTERED #
    //###############################################################

    // Drawing borders, backgrounds, etc
    ConsecutiveChar(TER, GAME_BORDER, gameWidth, true);
    ConsecutiveChar(TER, GAME_BORDER, 1, false);
    ConsecutiveChar(TER, GAME_BACKGROUND, seperationBetweenTextAndBorder, false);
    PrintInColour(TER, mapName, GAME_WINDOW_BACKGROUND_FG, GAME_WINDOW_BACKGROUND_BG);
    ConsecutiveChar(TER, GAME_BACKGROUND, seperationBetweenTextAndBorder, false);
    ConsecutiveChar(TER, GAME_BORDER, 1, true);

    //###############################################################
    //# TOP PORTION, DRAW THE DIVIDER BETWEEN TITLE AND MISCS       #
    //###############################################################
    ConsecutiveChar(TER, GAME_BORDER, 1, false);
    ConsecutiveChar(TER, GAME_DIVIDER_HORIZONTAL, seperationBetweenGameTimer, false);
    ConsecutiveChar(TER, GAME_DIVIDER_B_JUNCTION, 1, false);
    ConsecutiveChar(TER, GAME_DIVIDER_HORIZONTAL, GAME_FIELD_WIDTH_TIMER, false);
    ConsecutiveChar(TER, GAME_DIVIDER_B_JUNCTION, 1, false);
    ConsecutiveChar(TER, GAME_DIVIDER_HORIZONTAL, seperationBetweenGameTimer, false);
    ConsecutiveChar(TER, GAME_BORDER, 1, true);

    //###############################################################
    //# TOP PORTION, DRAW THE MISC BELOW THE TITLE                  #
    //###############################################################

    ConsecutiveChar(TER, GAME_BORDER, 1, false);
    ConsecutiveChar(TER, GAME_BACKGROUND, seperationBetweenGameTimer, false);
    ConsecutiveChar(TER, GAME_DIVIDER_VERTICAL, 1, false);
    ConsecutiveChar(TER, GAME_FIELD, GAME_FIELD_WIDTH_TIMER, false);
    ConsecutiveChar(TER, GAME_DIVIDER_VERTICAL, 1, false);
    ConsecutiveChar(TER, GAME_BACKGROUND, seperationBetweenGameTimer, false);
    ConsecutiveChar(TER, GAME_BORDER, 1, true);









    DrawGameHeader();
    DrawMap();
    DrawTimers();
    DrawInventories();
    DrawPlayerStatus();

    needToRedrawInventories = false;
    needToRedrawMap = false;
    needToRedrawPlayerStatus = false;
    needToRedrawTimers = false;
    return true;
}