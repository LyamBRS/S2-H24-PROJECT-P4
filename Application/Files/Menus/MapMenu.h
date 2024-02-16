/**
 * @file MapMenu.h
 * @author LyamBRS
 * @brief
 * Header definition of the MapMenu class
 * which allows a MapMenu to be handled.
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

class MapMenu : public Menu
{
    private:

    public:
        MapMenu(AppHandler* currentAppHandler);
        bool HandleKeyboard(int keyBoardKey);
        bool Draw();
        bool Update();
        bool OnEnter();
        bool OnExit();
};