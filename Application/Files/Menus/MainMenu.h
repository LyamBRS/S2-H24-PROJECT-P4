/**
 * @file MainMenu.h
 * @author LyamBRS
 * @brief
 * Header definition of the MainMenu class
 * which allows a MainMenu to be handled.
 * @version 0.1
 * @date 2024-02-15
 * @copyright Copyright (c) 2024
 */
#pragma once

// - INCLUDES - //
#include "../Application/AppHandler.h"
#include "../Colour/Colour.h"
#include <filesystem>
#include "Menu.h"
#include <vector>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>

// - DEFINES - //

// - CLASS - //
//class Application;

class cMainMenu : public cMenu
{
    private:
        int oldSelection = 0;
    public:
        cMainMenu(AppHandler* currentAppHandler);
        bool HandleKeyboard(int keyBoardKey);
        bool Draw();
        bool Update();
        bool OnEnter();
        bool OnExit();
};