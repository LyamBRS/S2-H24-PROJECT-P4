/**
 * @file TestMenu.h
 * @author LyamBRS
 * @brief
 * Header definition of the TestMenu class
 * which allows a TestMenu to be handled.
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

class TestMenu : public Menu
{
    private:

    public:
        TestMenu(AppHandler* currentAppHandler);
        bool HandleKeyboard(int keyBoardKey);
        bool Draw();
        bool OnEnter();
        bool OnExit();
        bool Update();
};