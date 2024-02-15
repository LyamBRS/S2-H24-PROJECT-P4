/**
 * @file ExitMenu.h
 * @author LyamBRS
 * @brief
 * Header definition of the ExitMenu class
 * which allows a ExitMenu to be handled.
 * @version 0.1
 * @date 2024-02-15
 * @copyright Copyright (c) 2024
 */
#pragma once

// - INCLUDES - //
#include "Menu.h"
#include "../Application/Application.h"

// - DEFINES - //

// - CLASS - //

class ExitMenu : public Menu
{
    private:

    public: 
        bool HandleKeyboard(int keyBoardKey);
        bool Draw();
        bool OnEnter();
        bool OnExit();
}