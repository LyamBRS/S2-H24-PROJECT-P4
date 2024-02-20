/**
 * @file TestMenu.cpp
 * @author LyamBRS
 * @brief
 * Header definition of the TestMenu class
 * which allows a TestMenu to be handled.
 * @version 0.1
 * @date 2024-02-15
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "TestMenu.h"

// - DEFINES - //

// - CLASS - //

TestMenu::TestMenu(AppHandler* currentAppHandler)
{
    appRef = currentAppHandler;
}

bool TestMenu::HandleKeyboard(int keyBoardKey)
{
    return false;
}

bool TestMenu::Draw()
{
    return false;
}

bool TestMenu::OnEnter()
{
    selection = 0;
    return false;
}

bool TestMenu::OnExit()
{
    selection = 0;
    return false;
}

bool TestMenu::Update()
{
    return false;
}