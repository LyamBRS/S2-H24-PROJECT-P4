/**
 * @file Menu.h
 * @author LyamBRS
 * @brief
 * Holds the abstract object Menu's
 * definition.
 * @version 0.1
 * @date 2024-02-15
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include "../Colour/Colour.h"
#include "../Application/Application.h"
#include <iostream>

// - DEFINES - //

// - CLASS - //

/**
 * @brief 
 * # Menu
 * @brief
 * Abstract class used to define the standard
 * methods within a standard Menu. These menus
 * are then used in the Application for various
 * reasons and purposes.
 */
class Menu 
{
    private:
        /// @brief A reference to the current application, allowing the menu to change things within the application.
        Application* appRef;
        /// @brief Defines the currently selected item within the menu.
        int selection = 0;
        /// @brief Should the menu redraw itself when @ref Update is called.
        bool needsRedrawing = false;

    public:

        /**
         * @brief 
         * # Menu
         * @brief
         * Abstract class used to define the standard
         * methods within a standard Menu. These menus
         * are then used in the Application for various
         * reasons and purposes.
         */
        Menu(Application* currentApp);

        /**
         * @brief 
         * Updates the menu. Redraws the screen if necessary
         * Handles the keyboard etc.
         * @return true 
         * @return false 
         */
        bool Update();

        /**
         * @brief 
         * Call to draw the menu.
         * @return true 
         * @return false 
         */
        bool Draw();

        /**
         * @brief 
         * Call to handle the keys pressed
         * and what they do in the application.
         * @param keyBoardKey 
         * @return true 
         * @return false 
         */
        bool HandleKeyboard(int keyBoardKey);

        /**
         * @brief 
         * Call if you want the menu to be
         * redrawn in the next frame.
         * @return true 
         * @return false 
         */
        bool RedrawNextFrame();

        /**
         * @brief 
         * Function executed when the menu is first loaded
         * in and becomes the active one.
         * @return true 
         * @return false 
         */
        bool OnEnter();

        /**
         * @brief 
         * Function executed when the menu is exited
         * and another menu is loaded instead.
         * @return true 
         * @return false 
         */
        bool OnExit();
};