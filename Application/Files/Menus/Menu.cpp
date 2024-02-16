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
 * # Menu
 * @brief
 * Abstract class used to define the standard
 * methods within a standard Menu. These menus
 * are then used in the Application for various
 * reasons and purposes.
 */
// Menu::Menu(AppHandler* currentAppHandler)
// {
    // std::cerr << "GOOD CONSTRUCTOR USED" << std::endl;
    // appRef = currentAppHandler;
// }

/**
 * @brief 
 * Updates the menu. Redraws the screen if necessary
 * Handles the keyboard etc.
 * @return true 
 * @return false 
 */
bool Menu::Update()
{
    return false;
}

/**
 * @brief 
 * Call to draw the menu.
 * @return true 
 * @return false 
 */
bool Menu::Draw()
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
bool Menu::HandleKeyboard(int keyBoardKey)
{
    return false;
}

/**
 * @brief 
 * Call if you want the menu to be
 * redrawn in the next frame.
 * @return true 
 * @return false 
 */
bool Menu::RedrawNextFrame()
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
bool Menu::OnEnter()
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
bool Menu::OnExit()
{
    return false;
}
