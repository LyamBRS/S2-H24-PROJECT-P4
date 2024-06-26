/**
 * @file Menu.cpp
 * @author LyamBRS
 * @brief 
 * Program associated with menus
 * @version 0.1
 * @date 2024-02-15
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "Menu.h"

// - PROGRAM - //

/**
 * @brief 
 * Updates the menu. Redraws the screen if necessary
 * Handles the keyboard etc.
 * @return true 
 * @return false 
 */
bool cMenu::Update()
{
    return false;
}

/**
 * @brief 
 * Call to draw the menu.
 * @return true 
 * @return false 
 */
bool cMenu::Draw()
{
    return false;
}

/**
 * @brief 
 * Call to handle the keys pressed
 * and what they do in the application.
 * @param keyBoardKey 
 * @return true 
 * @return false 
 */
bool cMenu::HandleKeyboard(int keyBoardKey)
{
    return keyBoardKey==0;
}

/**
 * @brief 
 * Call if you want the menu to be
 * redrawn in the next frame.
 * @return true 
 * @return false 
 */
bool cMenu::RedrawNextFrame()
{
    return false;
}

/**
 * @brief 
 * Function executed when the menu is first loaded
 * in and becomes the active one.
 * @return true 
 * @return false 
 */
bool cMenu::OnEnter()
{
    return false;
}

/**
 * @brief 
 * Function executed when the menu is exited
 * and another menu is loaded instead.
 * @return true 
 * @return false 
 */
bool cMenu::OnExit()
{
    return false;
}
