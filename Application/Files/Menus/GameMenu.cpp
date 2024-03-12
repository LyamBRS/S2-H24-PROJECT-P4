/**
 * @file GameMenu.cpp
 * @author LyamBRS
 * @brief
 * Holds the header definition of the GameMenu
 * class which allows a game to occur.
 * @version 0.1
 * @date 2024-02-15
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "GameMenu.h"

// - DEFINES - //

// - CLASS - //

GameMenu::GameMenu(AppHandler* currentAppHandler)
{
    appRef = currentAppHandler;
}

bool GameMenu::Update()
{
    if(!gameIsValid) return false;

    static int oldCountdownValue = 0;
    if(oldCountdownValue != currentGame->GetCountdownValue())
    {
        oldCountdownValue = currentGame->GetCountdownValue();
        Draw();
    }

    switch(currentGame->GetStatus())
    {
        case(GameStatuses::awaitingConnection):
        case(GameStatuses::awaitingPlayers):
        case(GameStatuses::ended):
        case(GameStatuses::playing):
            if(animationFrame.TimeLeft()==0)
            {
                animationSpriteIndex++;
                Draw();
            }
    }

    return currentGame->Update();
}

bool GameMenu::HandleKeyboard(int keyBoardKey)
{
    switch(currentGame->GetStatus())
    {
        case(GameStatuses::awaitingConnection):
            return KeyboardWaitingForConnection(keyBoardKey);
            break;

        case(GameStatuses::awaitingPlayers):
            return KeyboardWaitingForStart(keyBoardKey);
            break;

        case(GameStatuses::countdown):
            return KeyboardGame(keyBoardKey);
            break;

        case(GameStatuses::ended):
            return KeyboardEnd(keyBoardKey);
            break;

        case(GameStatuses::invalid):
            return KeyboardInvalid(keyBoardKey);
            break;

        case(GameStatuses::paused):
            return KeyboardPaused(keyBoardKey);
            break;

        case(GameStatuses::playing):
            return KeyboardGame(keyBoardKey);
            break;
    }
}

bool GameMenu::OnEnter()
{
    needsToBeRedrawn = true;

    // Get all available maps
    std::vector<nlohmann::json> allMaps = GetAllMaps();
    int amountOfMaps = allMaps.size();

    // Validate the given JSON of the specified index.
    if(appRef->wantedMapIndex < 0 || appRef->wantedMapIndex >= amountOfMaps)
    {
        gameIsValid = false;
        std::cout << "GAME wantedMapIndex ERROR" << std::endl;
        Sleep(1000);
        return false;
    }

    if(GetMapJsonError(allMaps[appRef->wantedMapIndex]) != EM_MAP_NO_ERROR)
    {
        std::cout << "GAME GetMapJsonError ERROR" << std::endl;
        Sleep(1000);
        gameIsValid = false;
        return false;
    }

    currentMap = new Map(allMaps[appRef->wantedMapIndex]);
    currentGame = new Game(appRef, currentMap);

    if(!currentGame->isValidated())
    {
        std::cout << "GAME isValidated ERROR" << std::endl;
        Sleep(1000);
        gameIsValid = false;
        return false;
    }
    gameIsValid = true;
    return true;
}

bool GameMenu::OnExit()
{
    needsToBeRedrawn = true;
    return true;
}

bool GameMenu::Draw()
{
    if(needsToBeRedrawn)
    {
        needsToBeRedrawn = false;
        system("cls");
    }
    SetTerminalCursorPosition(0,0);

    if(!gameIsValid) return DrawInvalid();

    switch(currentGame->GetStatus())
    {
        case(GameStatuses::awaitingConnection):
            return DrawWaitingForConnection();
            break;

        case(GameStatuses::awaitingPlayers):
            return DrawWaitingForStart();
            break;

        case(GameStatuses::countdown):
            return DrawStart();
            break;

        case(GameStatuses::ended):
            return DrawEnd();
            break;

        case(GameStatuses::invalid):
            return DrawInvalid();
            break;

        case(GameStatuses::paused):
            return DrawPaused();
            break;

        case(GameStatuses::playing):
            return DrawGame();
            break;
    }
}



bool GameMenu::DrawInvalid()
{
    system("cls");
    SetTerminalCursorPosition(0,0);
	std::cout << "############################################" << std::endl;
    std::cout << "               - GAME  ERROR -              " << std::endl;
    PrintInColour(std::cout, "           MAP CAUSES FATAL ERRORS        \n", colors::white, colors::red);
	std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Map number: " << std::to_string(appRef->wantedMapIndex) << std::endl;
    std::cout << "                    ";
    PrintInColour(std::cout, "[OK]\n", colors::black, colors::aqua);
	std::cout << "############################################" << std::endl;
    return true;
}

bool GameMenu::DrawWaitingForStart()
{
    auto rectangles = [](int amount, int color, bool lineEnd)
    {
        ConsecutiveChar(std::cout, ' ', colors::white, color, amount, lineEnd);
    };

    auto drawPlayerSlot = [](bool taken, int number, int type, int animationSpriteIndex)
    {
        std::string availableAnimationSprites[] = {
            "          ",
            "z         ",
            "Z         ",
            "Zz        ",
            "zZ        ",
            "zZz       ",
            "ZzZ       ",
            " zZz      ",
            " ZzZ      ",
            "  zZz     ",
            "  ZzZ     ",
            "   zZz    ",
            "   ZzZ    ",
            "    zZz   ",
            "    ZzZ   ",
            "     zZz  ",
            "     ZzZ  ",
            "      zZz ",
            "      ZzZ ",
            "       zZz",
            "        Zz",
            "        zZ",
            "         z",
            "         Z",
            "          ",
            "          ",
            "          "
        };

        std::string takenAnimationSprites[] = {
            "@      #  ",
            "@      +  ",
            "       #  ",
            "       +  ",
            "@      #  ",
            "@      +  ",
            "       #  ",
            "       +  ",
            "@      +  ",
            " @     +  ",
            "  @    +  ",
            "    @  +  ",
            "      @+ %",
            "     @ +%&",
            "    @ &%&%",
            "  @ %&%&%&",
            "@ &%&%&%&%",
            "%&%&%&%&%&",
            "&%&%&%&%&%",
            " &%&%&%&% ",
            " &%&%&%&% ",
            "  %&%&%&  ",
            "  %&%&%& #",
            "   &%& #  ",
            "   &% #   ",
            "   %  #   ",
            "       #  "
        };

        ConsecutiveChar(std::cout, ' ', colors::white, colors::black, 1, false);
        ConsecutiveChar(std::cout, '#', colors::lightgrey, BG, 1, false);
        ConsecutiveChar(std::cout, ' ', colors::lightgrey, colors::grey, 1, false);

        // Slot's type
        std::string slotValue = "   empty.   ";

        // Slot's name colour & taken values
        int colour = colors::grey;
        if(taken)
        {
            switch(type)
            {
                case(1):
                    colour = colors::lightred;
                    slotValue = "Controller A";
                    break;

                case(2):
                    colour = colors::leaf;
                    slotValue = "Controller B";
                    break;

                case(3):
                    colour = colors::blue;
                    slotValue = " L keyboard ";
                    break;
    
                case(4):
                    colour = colors::electric;
                    slotValue = " R keyboard ";
                    break;

                case(5):
                    colour = colors::darkpurple;
                    slotValue = "BRS  GamePad";
                    break;
            }
        }

        if(number<10)
        {
            PrintInColour(std::cout, " Player 0" + std::to_string(number), colour, colors::lightgrey);
        }
        else
        {
            PrintInColour(std::cout, " Player " + std::to_string(number), colour, colors::lightgrey);        
        }

        // Little seperation
        ConsecutiveChar(std::cout, ' ', BG, colors::lightgrey, 2, false);
        ConsecutiveChar(std::cout, '#', colors::lightgrey, BG, 1, false);
        ConsecutiveChar(std::cout, ' ', BG, colors::grey, 1, false);

        PrintInColour(std::cout, slotValue, colour, colors::lightgrey);
        ConsecutiveChar(std::cout, ' ', colors::lightgrey, colors::lightgrey, 1, false);
        ConsecutiveChar(std::cout, '#', colors::lightgrey, BG, 1, false);
        ConsecutiveChar(std::cout, ' ', colors::grey, colors::grey, 1, false);

        if(taken)
        {
            PrintInColour(std::cout, takenAnimationSprites[animationSpriteIndex], colour, colors::lightgrey);
        }
        else
        {
            PrintInColour(std::cout, availableAnimationSprites[animationSpriteIndex], colors::black, colors::lightgrey);
        }

        ConsecutiveChar(std::cout, '#', colors::lightgrey, BG, 1, false);
        ConsecutiveChar(std::cout, ' ', colors::grey, colors::grey, 1, true);
    };

    /**
     * @brief 
     * Animation sprites are from 0 to 27 in this menu.
     * They are thus kept within threshold only when drawn.
     */
    if(animationSpriteIndex > 26)
    {
        animationSpriteIndex = 0;
    }

    /**
     * WHOLE SECTION HERE IS JUST FOR THE LITTLE TOP.
     * WHERE BOMBERMAN IS DISPLAYED AND THE NAME OF THE MAP
     * FOLLOWS BELOW. Just having fun really...
     */
    rectangles(44, colors::black, true);                                                                                                                                //"############################################";
    rectangles(1, colors::black, false); rectangles(16, BG, false); PrintInColour(std::cout, "BOMBER MAN", colors::black, BG); rectangles(16, BG, false); rectangles(1, colors::black, true); //"#                BOMBER MAN                #";
    
    // Draw the name of the map dead center. Because why not.
    // To pull this off, we've got 42 characters of space to deal with.
    nlohmann::json mapJSON = currentGame->GetMap()->GetCurrentMap();
    std::string mapName = mapJSON["name"];
    int seperationBetweenTextAndBorder = (42-mapName.length())/2;

    rectangles(1, colors::black, false);
    rectangles(seperationBetweenTextAndBorder, BG, false);
    PrintInColour(std::cout, mapName, colors::black, BG);
    rectangles(seperationBetweenTextAndBorder, BG, false);

    if(mapName.length()%2 != 0)
    {
        rectangles(1, BG, false);
    }

    rectangles(1, colors::grey, true);
    rectangles(2, colors::black, false); rectangles(42, colors::grey, true);

    /**
     * @brief 
     * AREA WHERE PLAYER's CONNECTION STATUS IS STORED
     */
    rectangles(44, colors::black, true);
    rectangles(1, colors::black, false); ConsecutiveChar(std::cout, '#', colors::lightgrey, BG, 42, true);
    rectangles(1, colors::black, false); rectangles(9, BG, false); PrintInColour(std::cout, "Waiting for all players.", colors::black, BG); rectangles(9, BG, false);    rectangles(1, colors::grey, true);
    rectangles(1, colors::black, false); ConsecutiveChar(std::cout, '#', colors::lightgrey, BG, 42, false); rectangles(1, colors::grey, true);

    for(int i=0; i<currentGame->GetMap()->GetCurrentMap()["amountOfPlayers"]; i++)
    {
        drawPlayerSlot(!(i%2), i, i+1, animationSpriteIndex);
    }
    rectangles(1, colors::black, false); rectangles(42, colors::white, false); rectangles(1, colors::grey, true);
    rectangles(2, colors::black, false); rectangles(42, colors::grey, true);
    return false;
}

bool GameMenu::DrawWaitingForConnection()
{
    std::cout << "DrawWaitingForConnection" << std::endl;
    return false;
}

bool GameMenu::DrawPaused()
{
    std::cout << "DrawPaused" << std::endl;
    return false;
}

bool GameMenu::DrawGame()
{
    std::cout << "DrawGame" << std::endl;
    return false;
}

bool GameMenu::DrawStart()
{
    auto rectangles = [](int amount, int color, bool lineEnd)
    {
        ConsecutiveChar(std::cout, ' ', colors::white, color, amount, lineEnd);
    };

    rectangles(44, BC, true);
    rectangles(1, BC, false); rectangles(42, BG, false); rectangles(1, BC, true);
    rectangles(1, BC, false); rectangles(42, BG, false); rectangles(1, BC, true);

    switch(currentGame->GetCountdownValue())
    {
        case(4):
                rectangles(1, BC, false); rectangles(13, BG, false);     rectangles(12, C3, false); rectangles(17, BG, false);      rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(13, BG, false);     rectangles(12, C3, false); rectangles(17, BG, false);      rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(42, BG, false);     rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(42, BG, false);     rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(19, BG, false);     rectangles(12, C3, false); rectangles(11, BG, false);      rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(19, BG, false);     rectangles(12, C3, false); rectangles(11, BG, false);      rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(42, BG, false);     rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(42, BG, false);     rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(13, BG, false);     rectangles(12, C3, false); rectangles(17, BG, false);      rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(13, BG, false);     rectangles(12, C3, false); rectangles(17, BG, false);      rectangles(1, BC, true);
                break;

        case(3):
                rectangles(1, BC, false); rectangles(13, BG, false);     rectangles(15, C2, false); rectangles(14, BG, false);      rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(13, BG, false);     rectangles(15, C2, false); rectangles(14, BG, false);      rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(28, BG, false);     rectangles(3,  C2, false); rectangles(11, BG, false);       rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(28, BG, false);     rectangles(3,  C2, false); rectangles(11, BG, false);       rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(13, BG, false);     rectangles(18, C2, false); rectangles(11, BG, false);      rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(13, BG, false);     rectangles(18, C2, false); rectangles(11, BG, false);      rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(13, BG, false);     rectangles(3,  C2, false); rectangles(26, BG, false);       rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(13, BG, false);     rectangles(3,  C2, false); rectangles(26, BG, false);       rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(16, BG, false);     rectangles(15, C2, false); rectangles(11, BG, false);      rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(16, BG, false);     rectangles(15, C2, false); rectangles(11, BG, false);      rectangles(1, BC, true);
                break;

        case(2):
                rectangles(1, BC, false); rectangles(22, BG, false);     rectangles(3, C1, false); rectangles(17, BG, false);       rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(22, BG, false);     rectangles(3, C1, false); rectangles(17, BG, false);       rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(19, BG, false);     rectangles(6, C1, false); rectangles(17, BG, false);       rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(19, BG, false);     rectangles(6, C1, false); rectangles(17, BG, false);       rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(22, BG, false);     rectangles(3, C1, false); rectangles(17, BG, false);       rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(22, BG, false);     rectangles(3, C1, false); rectangles(17, BG, false);       rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(22, BG, false);     rectangles(3, C1, false); rectangles(17, BG, false);       rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(22, BG, false);     rectangles(3, C1, false); rectangles(17, BG, false);       rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(22, BG, false);     rectangles(3, C1, false); rectangles(17, BG, false);       rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(22, BG, false);     rectangles(3, C1, false); rectangles(17, BG, false);       rectangles(1, BC, true);
                break;

        case(1):
                rectangles(1, BC, false); rectangles(4, BG, false);      rectangles(15, CG, false); rectangles(7,  BG, false); rectangles(12, CG, false); rectangles(4, BG, false);    rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(4, BG, false);      rectangles(15, CG, false); rectangles(7,  BG, false); rectangles(12, CG, false); rectangles(4, BG, false);    rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(1, BG, false);      rectangles(3,  CG, false); rectangles(19, BG, false); rectangles(3,  CG, false); rectangles(12, BG, false);   rectangles(3, CG, false); rectangles(1, BG, false);   rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(1, BG, false);      rectangles(3,  CG, false); rectangles(19, BG, false); rectangles(3,  CG, false); rectangles(12, BG, false);   rectangles(3, CG, false); rectangles(1, BG, false);   rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(1, BG, false);      rectangles(3,  CG, false); rectangles(6,  BG, false); rectangles(9,  CG, false); rectangles(4, BG, false);    rectangles(3, CG, false); rectangles(12, BG, false); rectangles(3, CG, false); rectangles(1, BG, false);   rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(1, BG, false);      rectangles(3,  CG, false); rectangles(6,  BG, false); rectangles(9,  CG, false); rectangles(4, BG, false);    rectangles(3, CG, false); rectangles(12, BG, false); rectangles(3, CG, false); rectangles(1, BG, false);   rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(1, BG, false);      rectangles(3,  CG, false); rectangles(12, BG, false); rectangles(3,  CG, false); rectangles(4, BG, false);    rectangles(3, CG, false); rectangles(12, BG, false); rectangles(3, CG, false); rectangles(1, BG, false);   rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(1, BG, false);      rectangles(3,  CG, false); rectangles(12, BG, false); rectangles(3,  CG, false); rectangles(4, BG, false);    rectangles(3, CG, false); rectangles(12, BG, false); rectangles(3, CG, false); rectangles(1, BG, false);   rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(4, BG, false);      rectangles(12, CG, false); rectangles(10, BG, false); rectangles(12, CG, false); rectangles(4, BG, false);    rectangles(1, BC, true);
                rectangles(1, BC, false); rectangles(4, BG, false);      rectangles(12, CG, false); rectangles(10, BG, false); rectangles(12, CG, false); rectangles(4, BG, false);    rectangles(1, BC, true);
                break;
    }

    rectangles(1, BC, false); rectangles(42, BG, false); rectangles(1, BC, true);
    rectangles(1, BC, false); rectangles(42, BG, false); rectangles(1, BC, true);
    rectangles(44, BC, true);

    return true;
}

bool GameMenu::DrawEnd()
{
    std::cout << "DrawEnd" << std::endl;
    return false;
}



bool GameMenu::KeyboardInvalid(int keyBoardKey)
{
    appRef->currentSelectedMenu = APP_MAP_MENU;
    return true;
}

bool GameMenu::KeyboardWaitingForStart(int keyBoardKey)
{
    switch (keyBoardKey)
    {    
        case KB_RIGHT:
                return true;            
    
        case KB_LEFT:
                return true;                  

        case KB_ENTER: // Bypass playing joining wait.
                currentGame->Start();
                return true;
        
        case KB_ESCAPE:
                appRef->currentSelectedMenu = APP_MAP_MENU;
    }        
    return false;
}

bool GameMenu::KeyboardWaitingForConnection(int keyBoardKey)
{
    switch (keyBoardKey)
    {    
        case KB_RIGHT:
                return true;            
    
        case KB_LEFT:
                return true;                  

        case KB_ENTER:
                return true;
    }        
    return false;
}

bool GameMenu::KeyboardPaused(int keyBoardKey)
{
    switch (keyBoardKey)
    {    
        case KB_RIGHT:
                return true;            
    
        case KB_LEFT:
                return true;                  

        case KB_ENTER:
                return true;
    }        
    return false;
}

bool GameMenu::KeyboardGame(int keyBoardKey)
{
    switch (keyBoardKey)
    {    
        case KB_RIGHT:
                return true;            
    
        case KB_LEFT:
                return true;                  

        case KB_ENTER:
                return true;
    }        
    return false;
}

bool GameMenu::KeyboardStart(int keyBoardKey)
{
    switch (keyBoardKey)
    {    
        case KB_RIGHT:
                return true;            
    
        case KB_LEFT:
                return true;                  

        case KB_ENTER:
                return true;
    }        
    return false;
}

bool GameMenu::KeyboardEnd(int keyBoardKey)
{
    switch (keyBoardKey)
    {    
        case KB_RIGHT:
                return true;            
    
        case KB_LEFT:
                return true;                  

        case KB_ENTER:
                return true;
    }        
    return false;
}