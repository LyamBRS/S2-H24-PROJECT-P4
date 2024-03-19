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
    SetTerminalCursorPosition(0, GAME_CURSOR_MAP_Y);
    return map->Draw();
}

bool Game::DrawGameHeader()
{
    return false;
}

bool Game::DrawInventories()
{
    return false;
}

bool Game::DrawHealths()
{
    for(int playerIndex=0; playerIndex<players.size(); playerIndex++)
    {
        // That player is not used in the game.
        if(players[playerIndex].GetController()->controllerID == 0)
        {
            continue;
        }

        SetTerminalCursorPosition(healthCursorX, playerCardStartY + playerIndex);
        int playerHealth = players[playerIndex].Health();

        if(playerHealth == 0)
        {
            PrintInColour(TER, "DEAD", colors::black, GAME_WINDOW_FIELD_BG);
        }
        else
        {
            int bg = GAME_WINDOW_FIELD_BG;
            int fg = GAME_WINDOW_FIELD_BG;

            if(playerHealth > 90)      {fg = colors::white; bg = colors::green;}
            else if(playerHealth > 80) {fg = colors::lightgrey; bg = colors::green;}
            else if(playerHealth > 70) {fg = colors::leaf; bg = colors::grey;}
            else if(playerHealth > 60) {fg = colors::green; bg = colors::grey;}
            else if(playerHealth > 50) {fg = colors::yellow; bg = colors::grey;}
            else if(playerHealth > 40) {fg = colors::gold; bg = colors::grey;}
            else if(playerHealth > 30) {fg = colors::lightred; bg = colors::gold;}
            else if(playerHealth > 20) {fg = colors::red; bg = colors::gold;}
            else if(playerHealth > 10) {fg = colors::lightred; bg = colors::grey;}
            else                       {fg = colors::white; bg = colors::red;}

            ConsecutiveChar(TER, CHAR_HEARTH, fg, bg, 1, false);

            std::string result = std::to_string(playerHealth);
            while(result.size() != 3) result.insert(0, " ");
            PrintInColour(TER, result, fg, bg);
        }
    }
    return true;
}

bool Game::DrawPlayerStatus()
{
    for(int playerIndex=0; playerIndex<players.size(); playerIndex++)
    {
        int hasMovementCooldown = players[playerIndex].movementFrameDelay.TimeLeftNoReset();

        if(players[playerIndex].GetController()->controllerID != 0)
        {
            SetTerminalCursorPosition(bombStatusCursorX, playerCardStartY + playerIndex);
            // That player is no longer connected.
            if(!players[playerIndex].GetController()->isConnected)
            {
                PrintInColour(TER, "!", colors::white, colors::red);
                players[playerIndex].newStatus = 1;
            }
            // That player is out of health. He dead as hell.
            else if(players[playerIndex].Health() == 0)
            {
                PrintInColour(TER, STRING_HEARTH, colors::black, GAME_WINDOW_FIELD_BG);
                players[playerIndex].newStatus = 2;
            }
            else if(players[playerIndex].invulnurability.TimeLeftNoReset()!=0)
            {
                PrintInColour(TER, STRING_HEARTH, colors::red, GAME_WINDOW_FIELD_BG);
                players[playerIndex].newStatus = 3;
            }
            else if(hasMovementCooldown)
            {
                PrintInColour(TER, "M", colors::black, GAME_WINDOW_FIELD_BG);
                players[playerIndex].newStatus = 4;
            }
            // That player has no particular status to show
            else
            {
                PrintInColour(TER, " ", GAME_FIELD_COLORS);
                players[playerIndex].newStatus = 100;
            }

            if(players[playerIndex].newStatus != players[playerIndex].oldStatus)
            {
                players[playerIndex].oldStatus = players[playerIndex].newStatus;
                needToRedrawPlayerStatus = true;
            }
        }
    }

    return true;
}

bool Game::DrawTimers()
{
    SetTerminalCursorPosition(gameTimerCursorX, GAME_CURSOR_GAMETIMER_Y);

    unsigned char numSeconds = gameDuration.GetClockSeconds();
    unsigned char numMinutes = gameDuration.GetClockMinutes();
    unsigned char numHours = gameDuration.GetClockHours();

    std::string seconds = std::to_string(numSeconds);
    std::string minutes = std::to_string(numMinutes);
    std::string hours = std::to_string(numHours);

    if(seconds.length() == 1) seconds.insert(0, "0");
    if(minutes.length() == 1) minutes.insert(0, "0");
    if(hours.length() == 1) hours.insert(0, "0");

    std::string result = hours;
    result += ":";
    result += minutes;
    result += ":";
    result += seconds;

    PrintInColour(TER, result, GAME_FIELD_COLORS);
    needToRedrawTimers = false;
    return true;
}

bool Game::DrawCooldowns()
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
    int mapX = map->GetCurrentMap()["sizeX"];
    int mapY = map->GetCurrentMap()["sizeY"];

    for(int playerIndex=0; playerIndex<players.size(); playerIndex++)
    {
        // HandleMovements is done in each frame update. This governs 
        if(players[playerIndex].movementFrameDelay.TimeLeftNoReset() == 0)
        {
            int xVelocity = players[playerIndex].GetVelocity()->DeltaX();
            int yVelocity = players[playerIndex].GetVelocity()->DeltaY();

            int playerX = players[playerIndex].GetCurrentCoordinates()->X();
            int playerY = players[playerIndex].GetCurrentCoordinates()->Y();

            // Get wall coordinate for wall in front of player based on movements
            int testX = playerX + xVelocity;
            int testY = playerY + yVelocity;

            if(testX < 0) testX=0;
            if(testY < 0) testY=0;
            if(testX > mapX) testX=mapX;
            if(testY > mapY) testY=mapY;

            if ((xVelocity == 0) && (yVelocity == 0))
            {

            }
            else
            {
                TileTypes horizontalTileAtCoordinate = map->GetTileDataAtPosition(testX, playerY);
                TileTypes verticalTileAtCoordinate = map->GetTileDataAtPosition(playerX, testY);

                int horizontalVelocity = TileIsWalkable(horizontalTileAtCoordinate) ? xVelocity : 0;
                int verticalVelocity = TileIsWalkable(verticalTileAtCoordinate) ? yVelocity : 0;

                // Set new possible velocities based on tiles next to the player. Avoids diagonal clipping through walls
                players[playerIndex].GetVelocity()->SetDeltas(horizontalVelocity, verticalVelocity);

                testX = playerX + horizontalVelocity;
                testY = playerY + verticalVelocity;
                if(testX < 0) testX=0;
                if(testY < 0) testY=0;
                if(testX > mapX) testX=mapX;
                if(testY > mapY) testY=mapY;

                // Get the new, fixed position to analyse
                TileTypes tileAtWantedDestination = map->GetTileDataAtPosition(testX, testY);

                if(!TileIsWalkable(tileAtWantedDestination))
                {
                    players[playerIndex].GetVelocity()->ResetDeltas();
                }
                else
                {
                    players[playerIndex].movementFrameDelay.Reset();
                    players[playerIndex].GetCurrentCoordinates()->SetNewCoordinates(testX, testY);
                }
            }
        }
    }
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
    if(flipDrawingOrder)
    {
        PutPlayersInMap();
        PutBombsInMap();
        PutPowerUpsInMap();
    }
    else
    {
        PutPowerUpsInMap();
        PutBombsInMap();
        PutPlayersInMap();
    }

    return true;
}

bool Game::PutPlayersInMap()
{
    // Place players on the map.
    for (int playerIndex = 0; playerIndex < players.size(); playerIndex++)
    {
        Player* currentPlayer = &players[playerIndex];
        Positions* previousPos = players[playerIndex].GetOldCoordinates();
        Positions* currentPos = players[playerIndex].GetCurrentCoordinates();

        if (currentPlayer->GetController()->controllerID != 0) // Otherwise, that player was not assigned a controller, thus is not playing.
        {
            // Player needs to be removed from the map.
            if (currentPlayer->NeedsToBeDeleted())
            {
                needToRedrawMap = true;
                currentPlayer->SetPlayerAsDeleted();
                map->SetTileDataAtPosition(currentPos->X(), previousPos->Y(), TileTypes::EMPTY);
                map->SetTileDataAtPosition(previousPos->X(), previousPos->Y(), TileTypes::EMPTY);
            }
            else // Puts an empty space behind the player, and put the current player innit
            {
                if ((currentPos->X() != previousPos->X()) || (currentPos->Y() != previousPos->Y()))
                {
                    needToRedrawMap = true;
                    if (!map->SetTileDataAtPosition(previousPos->X(), previousPos->Y(), TileTypes::EMPTY))
                    {
                        SetTerminalCursorPosition(0, 0);
                        std::cout << "FAILED PREVIOUS" << std::endl;
                        Sleep(1000);
                    }
                    if (!map->SetTileDataAtPosition(currentPos->X(), currentPos->Y(), map->GetPlayerTypeFromId(playerIndex)))
                    {
                        SetTerminalCursorPosition(0, 0);
                        std::cout << "FAILED CURRENT" << std::endl;
                        Sleep(1000);
                    }
                    previousPos->SetNewCoordinates(currentPos->X(), currentPos->Y());
                    needToRedrawMap = true;
                }
                else
                {
                    if (!checkIfTileIsPlayer(map->GetTileDataAtPosition(currentPos->X(), currentPos->Y())))
                    {
                        map->SetTileDataAtPosition(currentPos->X(), currentPos->Y(), map->GetPlayerTypeFromId(playerIndex));
                        needToRedrawMap = true;
                    }
                }
            }
        }
    }
    return true;
}

bool Game::PutBombsInMap()
{
    for (int bombIndex = 0; bombIndex<bombsOnMap.size(); bombIndex++)
    {
        if(bombsOnMap[bombIndex].IsExploding())
        {
            bombsOnMap[bombIndex].Draw();
            needToRedrawMap = true;
        }
        else
        {
            if(map->GetTileDataAtPosition(*bombsOnMap[bombIndex].GetCurrentCoordinates()) != TileTypes::BOMB)
            {
                needToRedrawMap = true;
            }
            map->SetTileDataAtPosition(
                bombsOnMap[bombIndex].GetCurrentCoordinates()->X(), 
                bombsOnMap[bombIndex].GetCurrentCoordinates()->Y(), 
                TileTypes::BOMB);
        }
    }
    return true;
}

bool Game::PutPowerUpsInMap()
{
    for(int i=0; i<itemsOnMap.size(); i++)
    {
        Positions powerUpPos = *itemsOnMap[i].GetCurrentCoordinates();
        TileTypes associatedTile = GetTileFromPowerUp(itemsOnMap[i].GetType());

        //SetTerminalCursorPosition(60,i);
        //PrintTileName(associatedTile);
        //std::cout << ": " << itemsOnMap[i].GetType();

        map->SetTileDataAtPosition(
           powerUpPos.X(),
           powerUpPos.Y(),
           associatedTile
        );
    }
    return true;
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
    // Handle placement of new bombs on the map.
    for (int playerIndex = 0; playerIndex < players.size(); playerIndex++)
    {
        Player* currentPlayer = &players[playerIndex];
        if(currentPlayer->WantsToPlaceABomb())
        {
            currentPlayer->PlacedABomb();
            PlacedBomb newBomb = PlacedBomb(
                currentPlayer->GetCurrentCoordinates()->X(),
                currentPlayer->GetCurrentCoordinates()->Y(),
                GAME_DEFAULT_BOMB_RADIUS,
                2000,
                map
            );
            bombsOnMap.push_back(newBomb);
        }
    }

    // Update all the bombs currently on the map.
    // Also checks if they have finished exploding to clear and remove them.
    if(bombUpdateTimer.TimeLeft() == 0)
    {
        for(int i=0; i<bombsOnMap.size(); i++)
        {
            bombsOnMap[i].Update();
            if (bombsOnMap[i].HasFinishedExploding())
            {
                // Clear all the smoke from the map.
                bombsOnMap[i].Clear();
                // Check if tile is a bomb, if so, replace with empty tile.
                Positions bombPlacement = *bombsOnMap[i].GetCurrentCoordinates();
                if (map->GetTileDataAtPosition(bombPlacement) == TileTypes::BOMB)
                {
                    map->SetTileDataAtPosition(
                        bombPlacement.X(),
                        bombPlacement.Y(),
                        TileTypes::EMPTY
                    );
                }

                // Check the ends of raycasts to remove boxes.
                for(int rayIndex=0; rayIndex<bombsOnMap[i].rays.size(); rayIndex++)
                {
                    if(bombsOnMap[i].rays[rayIndex].HasEnded())
                    {
                        Positions raysEndPos = bombsOnMap[i].rays[rayIndex].GetEndPosition();
                        TileTypes tileAtEndOfRay = map->GetTileDataAtPosition(raysEndPos);
    
                        if(tileAtEndOfRay == TileTypes::WALL) // Can be destroyed
                        {
                            HandleBoxDestruction(raysEndPos);
                        }
                    }
                }
            }
        }
    }

    // Delete the exploded bombs
    for(int i=0; i<bombsOnMap.size(); i++)
    {
        if(bombsOnMap[i].HasFinishedExploding())
        {
            bombsOnMap.erase(bombsOnMap.begin() + i);
        }
    }

    return true;
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
    // Update all controllers of the players.
    for (int playerIndex = 0; playerIndex < players.size(); playerIndex++)
    {
        players[playerIndex].UpdateFromController();
        int playerHealth = players[playerIndex].Health();
        int wantedBits = 0;
        switch((playerHealth/10))
        {
            case(10): wantedBits = wantedBits ^= 1;
            case(9): wantedBits = wantedBits ^= 2;
            case(8): wantedBits = wantedBits ^= 4;
            case(7): wantedBits = wantedBits ^= 8;
            case(6): wantedBits = wantedBits ^= 16;
            case(5): wantedBits = wantedBits ^= 32;
            case(4): wantedBits = wantedBits ^= 64;
            case(3): wantedBits = wantedBits ^= 128;
            case(2): wantedBits = wantedBits ^= 256;
            case(1): wantedBits = wantedBits ^= 512;
        }
        players[playerIndex].GetController()->SentBarGraphBits = wantedBits;
    }
    HandleNextMouvements();
    return true;
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
    for(int i=0; i<players.size(); i++)
    {
        Positions playerCurrentPositions = *players[i].GetCurrentCoordinates();
        TileTypes tileUnderPlayer = map->GetTileDataAtPosition(playerCurrentPositions);

        if(tileUnderPlayer == TileTypes::SMOKE) // Player is currently inside of a smoke tile
        {
            players[i].GiveDamage(GAME_DEFAULT_DAMAGE);
            needToRedrawPlayerHealth = true;
        }
    }
    return false;
}

bool Game::HandleBoxDestruction(Positions boxPosition)
{
    // MUON STUFF HERE.
    int detectedMuons = appRef->GetDetectedMuons();

    // CHANGE THIS ONCE WE'VE GOT MUONS GOING
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6); // distribution in range [1, 6]

    // - DESTROY BOX - //
    map->SetTileDataAtPosition(
        boxPosition.X(),
        boxPosition.Y(),
        TileTypes::EMPTY
    );

    int randomNumber = dist6(rng);
    TileTypes wantedTile = TileTypes::EMPTY;
    switch(randomNumber)
    {
        case(0):
            wantedTile = TileTypes::POWER_DMG;
            break;

        case(1):
            wantedTile = TileTypes::POWER_HEART;
            break;

        case(2):
            wantedTile = TileTypes::POWER_MOREBOMB;
            break;

        case(3):
            wantedTile = TileTypes::POWER_REACH;
            break;

        case(4):
            wantedTile = TileTypes::POWER_SPEED;
            break;
    }

    // - Test if the tile is no longer empty. If thats the case, a powerup needs to be created.
    if(wantedTile != TileTypes::EMPTY)
    {
        itemsOnMap.push_back(PlacedPowerUp(
            boxPosition.X(),
            boxPosition.Y(),
            GetPowerUpFromTile(wantedTile)
        ));
    }

    // SetTerminalCursorPosition(0,0);
    // std::cout << "Created powerup with ID " << GetPowerUpFromTile(wantedTile) << " tile name: ";
    // PrintTileName(wantedTile);
    // std::cout << " at coordinates: " << boxPosition.X() << "," << boxPosition.Y() << std::endl;
    // Sleep(1000);

    return true;
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
    // And other cursor related positions on the terminal window, which will be used to draw later
    int mapSizeX = map->GetCurrentMap()["sizeX"];
    int mapSizeY = map->GetCurrentMap()["sizeY"];
    int amountOfPlayers = map->GetCurrentMap()["amountOfPlayers"];
    gameWidth = mapSizeX*3;

    if(gameWidth < GAME_MIN_WIDTH)  gameWidth = GAME_MIN_WIDTH;
    if(gameWidth%2 != 0) gameWidth++;

    // Other position related things
    mapCursorX = 0;
    mapCursorY = GAME_HEADER_HEIGHT;

    gameTimerOffset = ((gameWidth-4) - GAME_FIELD_WIDTH_TIMER)/2;
    gameTimerCursorX = 1 + gameTimerOffset + 1;

    playerCardOffsetX = ((gameWidth-GAME_MIN_WIDTH)/2);

    // static text field + borders around it + offset + game border.
    cooldownCursorX = GAME_FIELD_WIDTH_PLAYER_NAME + 2 + playerCardOffsetX + 1;
    bombStatusCursorX = cooldownCursorX + GAME_FIELD_WIDTH_COOLDOWN + 1;
    healthCursorX = bombStatusCursorX + GAME_FIELD_WIDTH_BOMB_STATUS + 1;
    inventoryCursorX = healthCursorX + GAME_FIELD_WIDTH_HEALTH + 1;

    playerCardStartY = (6 + mapSizeY + 4)-1;

    // Create as much players as there is for that specific map.
    for(int playerIndex=0; playerIndex<amountOfPlayers; playerIndex++)
    {
        unsigned int initialPosX = 0;
        unsigned int initialPosY = 0;

        if(!map->GetASpawnPosition(playerIndex, &initialPosX, &initialPosY))
        {
            // Map does not have as much spawnpoints as it advertises
            std::cout << "FATAL PLAYER SPAWN ERROR. False was returned. ERROR BYPASSED" << std::endl;
            Sleep(500);
            errorMessage = "FATAL PLAYER SPAWN ERROR";
            canBeUsed = false;
            gameStatus = GameStatuses::invalid;
            //return;
        }
        Player player = Player(initialPosX, initialPosY, " @ ", GetPlayerColor(playerIndex));
        players.push_back(player);
    }

    gameHeight = 6 + mapSizeY + 2 + amountOfPlayers;

    // std::cout << "GAME CAN NOW BE USED" << std::endl;
    // Sleep(1000);

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
    static int oldGameStatus = GameStatuses::invalid;
    static uint8_t oldSeconds = 0;

    /////////////////////////////////////////
    // Handling game status changes
    /////////////////////////////////////////
    if(gameStatus != oldGameStatus)
    {
        statusChanged = true;
        // Game actually started! This is the first update frame.
        if(oldGameStatus==GameStatuses::countdown && gameStatus==GameStatuses::playing)
        {
            gameDuration.Start(); // Start the timer at the top.
        }
        oldGameStatus = gameStatus;
    }

    ////////////////////////////////////////////
    // Handling Game duration drawing intervals
    ////////////////////////////////////////////
    if(oldSeconds != gameDuration.GetClockSeconds())
    {
        oldSeconds = gameDuration.GetClockSeconds();
        needToRedrawTimers = true;
    }

    ////////////////////////////////////////////
    // Handle game attributes
    ////////////////////////////////////////////
    if(gameStatus == GameStatuses::playing)
    {
        HandlePlayers();
        HandleBombs();
        HandlePowerUp();
        PutObjectsInMap();
        CheckForPlayerDamage();
    }

    if(drawingFlipper.TimeLeft()==0) flipDrawingOrder = !flipDrawingOrder;

    ////////////////////////////////////////////
    // Handle game end.
    ////////////////////////////////////////////
    if(gameStatus == GameStatuses::playing)
    {
        int ID = GetWinningPlayerID();
        if(ID != -1)
        {
            gameStatus = GameStatuses::ended;
        }
    }

    return true;
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
 * Pauses the game. This changes the status of the
 * game according to @ref GameStatuses allowing
 * it to freeze in time until it is @ref Resumed.
 * @return true:
 * Game was paused successfully
 * @return false:
 * Game is not started / already paused / invalid. 
 */
bool Game::Pause()
{
    if(gameStatus != GameStatuses::playing) return false;
    gameStatus = GameStatuses::paused;
    gameDuration.Stop();
    return true;
}

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
bool Game::Resume()
{
    if((gameStatus != GameStatuses::paused) || (gameStatus == GameStatuses::awaitingConnection)) return false;
    SetTerminalCursorPosition(0,0);
    // std::cout << "GAME RESUMED" << std::endl;
    // Sleep(1000);
    gameStatus = GameStatuses::playing;
    gameDuration.Resume();
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
    HandleNextMouvements();
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



Controller* Game::GetPlayerController(int playerIndex)
{
    if(!canBeUsed)
    {
        std::cout << "GAME CONSTRUCTOR ERROR: GetPlayerController: NO PLAYERS IN VECTOR" << std::endl;
        Sleep(1000);
        return nullptr;
    }

    if(players.size() == 0)
    {
        std::cout << "GAME CONSTRUCTOR ERROR: GetPlayerController: NO PLAYERS IN VECTOR... AGAIN?!?" << std::endl;
        Sleep(1000);
        return nullptr;
    }

    return players[playerIndex].GetController();
}

bool Game::AssignControllerToPlayer(int playerIndex, Controller* controllerRef)
{
    if(!canBeUsed) {std::cout << "GAME CONSTRUCTOR ERROR: AssignControllerToPlayer: NO PLAYERS IN VECTOR" << std::endl; return false;}
    return players[playerIndex].LinkController(controllerRef);
}

bool Game::UnAssignPlayerController(int playerIndex)
{
    players[playerIndex].UnlinkController();
    return true;
}

int Game::GetWinningPlayerID()
{
    int amountOfPlayersAlive = 0;
    int lastPlayerID = 0;
    for(int i=0; i<players.size(); i++)
    {
        if((players[i].Health() != 0) && (players[i].GetController()->controllerID!=0))
        {
            amountOfPlayersAlive++;
            lastPlayerID = i;
        }
    }

    if(amountOfPlayersAlive == 1) return lastPlayerID;
    if(amountOfPlayersAlive == 0) return 0;
    return -1;
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
    return needToRedrawInventories || needToRedrawMap || needToRedrawPlayerStatus || needToRedrawTimers || needToRedrawPlayerHealth;
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

    if(statusChanged)
    {
        statusChanged = false;
        if(gameStatus == GameStatuses::playing)
        {
            FreshDraw();
        }
    }

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

    needToRedrawPlayerStatus = true;
    if(needToRedrawPlayerStatus)
    {
        needToRedrawPlayerStatus = false;
        DrawPlayerStatus();
    }

    if(needToRedrawPlayerHealth)
    {
        needToRedrawPlayerHealth = false;
        DrawHealths();
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
    ResizeTerminal(gameWidth-1, gameHeight-1);
    if(!canBeUsed) return false;

    // Terminal needs to be resized to proper dimensions
    static bool doOnce = false;
    if(!doOnce)
    {
        ResizeTerminal(gameWidth, gameHeight);
        doOnce = false;
    }

    auto FreshDrawPlayer = [](int playerNumber, int gameWidth){

        // Centers the players cards within the borders
        int offset = ((gameWidth-30)/2);

        // Create the player's name
        std::string playerName = "Player ";
        if(playerNumber < 10) playerName.append("0");
        playerName.append(std::to_string(playerNumber));

        // Leading up to the area where player data is displayed.
        ConsecutiveChar(TER, GAME_BORDER, 1, false);
        ConsecutiveChar(TER, GAME_BACKGROUND, offset, false);

        // Player name
        ConsecutiveChar(TER, GAME_DIVIDER_VERTICAL, 1, false);
        PrintInColour(TER, playerName, GetPlayerColor(playerNumber), GAME_WINDOW_FIELD_BG);

        // Bomb cooldown
        ConsecutiveChar(TER, GAME_DIVIDER_VERTICAL, 1, false);
        ConsecutiveChar(TER, GAME_FIELD, GAME_FIELD_WIDTH_COOLDOWN, false);

        // Lil status
        ConsecutiveChar(TER, GAME_DIVIDER_VERTICAL, 1, false);
        ConsecutiveChar(TER, GAME_FIELD, GAME_FIELD_WIDTH_BOMB_STATUS, false);

        // Health display
        ConsecutiveChar(TER, GAME_DIVIDER_VERTICAL, 1, false);
        ConsecutiveChar(TER, GAME_FIELD, GAME_FIELD_WIDTH_HEALTH, false);

        // Inventory
        ConsecutiveChar(TER, GAME_DIVIDER_VERTICAL, 1, false);
        ConsecutiveChar(TER, GAME_FIELD, GAME_FIELD_WIDTH_INVENTORY, false);

        // End of the player's card.
        ConsecutiveChar(TER, GAME_DIVIDER_VERTICAL, 1, false);
        ConsecutiveChar(TER, GAME_BACKGROUND, offset, false);
        ConsecutiveChar(TER, GAME_BORDER, 1, true);  
    };

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

    //###############################################################
    //# TOP PORTION OF THE GAME
    //###############################################################

    // DRAW THE NAME OF THE MAP, CENTERED
    ConsecutiveChar(TER, GAME_BORDER, gameWidth, true);
    ConsecutiveChar(TER, GAME_BORDER, 1, false);
    ConsecutiveChar(TER, GAME_BACKGROUND, seperationBetweenTextAndBorder, false);
    PrintInColour(TER, mapName, GAME_WINDOW_BACKGROUND_FG, GAME_WINDOW_BACKGROUND_BG);
    ConsecutiveChar(TER, GAME_BACKGROUND, seperationBetweenTextAndBorder, false);
    ConsecutiveChar(TER, GAME_BORDER, 1, true);

    // DRAW THE DIVIDER BETWEEN TITLE AND MISCS
    ConsecutiveChar(TER, GAME_BORDER, 1, false);
    ConsecutiveChar(TER, GAME_DIVIDER_HORIZONTAL, gameTimerOffset, false);
    ConsecutiveChar(TER, GAME_DIVIDER_B_JUNCTION, 1, false);
    ConsecutiveChar(TER, GAME_DIVIDER_HORIZONTAL, GAME_FIELD_WIDTH_TIMER, false);
    ConsecutiveChar(TER, GAME_DIVIDER_B_JUNCTION, 1, false);
    ConsecutiveChar(TER, GAME_DIVIDER_HORIZONTAL, gameTimerOffset, false);
    ConsecutiveChar(TER, GAME_BORDER, 1, true);

    //DRAW THE MISC BELOW THE TITLE
    ConsecutiveChar(TER, GAME_BORDER, 1, false);
    ConsecutiveChar(TER, GAME_BACKGROUND, gameTimerOffset, false);
    ConsecutiveChar(TER, GAME_DIVIDER_VERTICAL, 1, false);
    ConsecutiveChar(TER, GAME_FIELD, GAME_FIELD_WIDTH_TIMER, false);
    ConsecutiveChar(TER, GAME_DIVIDER_VERTICAL, 1, false);
    ConsecutiveChar(TER, GAME_BACKGROUND, gameTimerOffset, false);
    ConsecutiveChar(TER, GAME_BORDER, 1, true);

    //# BOTTOM OF THE HEADER, LEAVING 1 BLACK EMPTY SPACE BEFORE MAP#
    ConsecutiveChar(TER, GAME_BORDER, gameWidth, true);
    ConsecutiveChar(TER, ' ', colors::black, colors::black, gameWidth, true);


    //###############################################################
    //# MAP PORTION, leaving 1 black line below it.                 #
    //###############################################################
    DrawMap();
    ConsecutiveChar(TER, ' ', colors::black, colors::black, gameWidth, true);

    //###############################################################
    //# Player stats portion                                        #
    //###############################################################

    // Border before the chaos
    ConsecutiveChar(TER, GAME_BORDER, gameWidth, true);

    // TOP DIVIDER
    ConsecutiveChar(TER, GAME_BORDER, 1, false);
    ConsecutiveChar(TER, GAME_BACKGROUND, playerCardOffsetX, false);
    ConsecutiveChar(TER, GAME_DIVIDER_TL_CORNER, 1, false);
    ConsecutiveChar(TER, GAME_DIVIDER_HORIZONTAL, GAME_FIELD_WIDTH_PLAYER_NAME, false);
    ConsecutiveChar(TER, GAME_DIVIDER_B_JUNCTION, 1, false);
    ConsecutiveChar(TER, GAME_DIVIDER_HORIZONTAL, GAME_FIELD_WIDTH_COOLDOWN, false);
    ConsecutiveChar(TER, GAME_DIVIDER_B_JUNCTION, 1, false);
    ConsecutiveChar(TER, GAME_DIVIDER_HORIZONTAL, GAME_FIELD_WIDTH_BOMB_STATUS, false);
    ConsecutiveChar(TER, GAME_DIVIDER_B_JUNCTION, 1, false);
    ConsecutiveChar(TER, GAME_DIVIDER_HORIZONTAL, GAME_FIELD_WIDTH_HEALTH, false);
    ConsecutiveChar(TER, GAME_DIVIDER_B_JUNCTION, 1, false);
    ConsecutiveChar(TER, GAME_DIVIDER_HORIZONTAL, GAME_FIELD_WIDTH_INVENTORY, false);
    ConsecutiveChar(TER, GAME_DIVIDER_TR_CORNER, 1, false);
    ConsecutiveChar(TER, GAME_BACKGROUND, playerCardOffsetX, false);
    ConsecutiveChar(TER, GAME_BORDER, 1, true);

    // ALL PLAYER CARDS. AS MANY AS THERE IS PLAYERS FOR THIS GAME
    for(int playerIndex = 0; playerIndex < map->GetCurrentMap()["amountOfPlayers"]; playerIndex++)
    {
        if(players[playerIndex].GetController()->controllerID != 0) 
        {
            FreshDrawPlayer(playerIndex, gameWidth);

            // Replace the player spawn by the actual player
            map->SetTileDataAtPosition(
                players[playerIndex].GetCurrentCoordinates()->X(), 
                players[playerIndex].GetCurrentCoordinates()->Y(),
                map->GetPlayerTypeFromId(playerIndex)
            );
        }
        else
        {
            // Player did not join. Replace by empty space
            map->SetTileDataAtPosition(
                players[playerIndex].GetCurrentCoordinates()->X(), 
                players[playerIndex].GetCurrentCoordinates()->Y(),
                TileTypes::EMPTY
            );
        }
    }

    // BOTTOM DIVIDER
    ConsecutiveChar(TER, GAME_BORDER, 1, false);
    ConsecutiveChar(TER, GAME_BACKGROUND, playerCardOffsetX, false);
    ConsecutiveChar(TER, GAME_DIVIDER_BL_CORNER, 1, false);
    ConsecutiveChar(TER, GAME_DIVIDER_HORIZONTAL, GAME_FIELD_WIDTH_PLAYER_NAME, false);
    ConsecutiveChar(TER, GAME_DIVIDER_T_JUNCTION, 1, false);
    ConsecutiveChar(TER, GAME_DIVIDER_HORIZONTAL, GAME_FIELD_WIDTH_COOLDOWN, false);
    ConsecutiveChar(TER, GAME_DIVIDER_T_JUNCTION, 1, false);
    ConsecutiveChar(TER, GAME_DIVIDER_HORIZONTAL, GAME_FIELD_WIDTH_BOMB_STATUS, false);
    ConsecutiveChar(TER, GAME_DIVIDER_T_JUNCTION, 1, false);
    ConsecutiveChar(TER, GAME_DIVIDER_HORIZONTAL, GAME_FIELD_WIDTH_HEALTH, false);
    ConsecutiveChar(TER, GAME_DIVIDER_T_JUNCTION, 1, false);
    ConsecutiveChar(TER, GAME_DIVIDER_HORIZONTAL, GAME_FIELD_WIDTH_INVENTORY, false);
    ConsecutiveChar(TER, GAME_DIVIDER_BR_CORNER, 1, false);
    ConsecutiveChar(TER, GAME_BACKGROUND, playerCardOffsetX, false);
    ConsecutiveChar(TER, GAME_BORDER, 1, true);

   // Border after the chaos
    ConsecutiveChar(TER, GAME_BORDER, gameWidth, true);

    DrawGameHeader();
    DrawTimers();
    DrawInventories();
    DrawPlayerStatus();
    DrawHealths();

    needToRedrawInventories = false;
    needToRedrawMap = false;
    needToRedrawPlayerStatus = false;
    needToRedrawTimers = false;
    return true;
}