/**
 * @file MapMenu.cpp
 * @author LyamBRS
 * @brief
 * Header definition of the ExitMenu class
 * which allows a ExitMenu to be handled.
 * @version 0.1
 * @date 2024-02-15
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "MapMenu.h"

// - DEFINES - //

// - CLASS - //

MapMenu::MapMenu(AppHandler* currentAppHandler)
{
    appRef = currentAppHandler;
}

bool MapMenu::HandleKeyboard(int keyBoardKey)
{
    return false;
}

bool MapMenu::Draw()
{
    return false;
}

bool MapMenu::OnEnter()
{
    selection = 0;
    return false;
}

bool MapMenu::OnExit()
{
    selection = 0;
    return false;
}

bool MapMenu::Update()
{
    return false;
}