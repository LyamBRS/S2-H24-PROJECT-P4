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
#include "Menu.h"

// - DEFINES - //

// - CLASS - //
//class Application;

class MainMenu : public Menu
{
    private:

    public:
        MainMenu(AppHandler* currentAppHandler);
        bool HandleKeyboard(int keyBoardKey);
        bool Draw();
        bool Update();
        bool OnEnter();
        bool OnExit();
};