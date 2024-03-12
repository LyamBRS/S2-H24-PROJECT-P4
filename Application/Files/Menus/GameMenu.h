/**
 * @file GameMenu.h
 * @author LyamBRS
 * @brief
 * Holds the header definition of the GameMenu
 * class which allows a game to occur.
 * @version 0.1
 * @date 2024-03-11
 * @copyright Copyright (c) 2024
 */
#pragma once

// - INCLUDES - //
#include "Menu.h"
#include "../Application/AppHandler.h"
#include "../Colour/Colour.h"
#include "../Game/Game.h"
#include "../Map/Map.h"
#include "../Map/Utils.hpp"
#include "../JSON/json.hpp"
#include "../SimpleTimer/SimpleTimer.h"
#include <vector>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>

// - DEFINES - //
#define BC colors::darkpurple  // Border color
#define BG colors::white       // Background colour
#define C3 colors::green       // color for number 3
#define C2 colors::gold        // color for number 2
#define C1 colors::red         // color for number 1
#define CG colors::darkpurple  // color for the GO text
// - CLASS - //

// - GLOBALS - //

class GameMenu : public Menu
{
    private:
        bool needsToBeRedrawn = false;
        bool gameIsValid = false;
        Game* currentGame = new Game();
        Map* currentMap;

        SimpleTimer frameDelay = SimpleTimer(30);
        SimpleTimer animationFrame = SimpleTimer(100);

        int animationSpriteIndex = 0;

    public:
        GameMenu(AppHandler* currentAppHandler);
        bool HandleKeyboard(int keyBoardKey);
        bool Update();
        bool Draw();
        bool OnEnter();
        bool OnExit();

        bool DrawInvalid();
        bool DrawWaitingForStart();
        bool DrawWaitingForConnection();
        bool DrawPaused();
        bool DrawGame();
        bool DrawStart();
        bool DrawEnd();

        bool KeyboardInvalid(int keyBoardKey);
        bool KeyboardWaitingForStart(int keyBoardKey);
        bool KeyboardWaitingForConnection(int keyBoardKey);
        bool KeyboardPaused(int keyBoardKey);
        bool KeyboardGame(int keyBoardKey);
        bool KeyboardStart(int keyBoardKey);
        bool KeyboardEnd(int keyBoardKey);
};