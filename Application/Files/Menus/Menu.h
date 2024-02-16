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
#include "../Application/AppHandler.h"
#include <iostream>

// - DEFINES - //
#define APP_MAIN_MENU 0
#define APP_ARDUINO_MENU 2
#define APP_GAME_MENU 3
#define APP_TEST_MENU 1
#define APP_EXIT_MENU 4

#define KB_UP 72
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77
#define KB_ESCAPE 27
#define KB_ENTER 13

// - CLASS - //
// class Application;

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
    public:

        /// @brief A reference to the current application, allowing the menu to change things within the application.
        AppHandler* appRef = nullptr;
        /// @brief Defines the currently selected item within the menu.
        int selection = 0;
        /// @brief Should the menu redraw itself when @ref Update is called.
        bool needsRedrawing = false;

        /**
         * @brief 
         * # Menu
         * @brief
         * Abstract class used to define the standard
         * methods within a standard Menu. These menus
         * are then used in the Application for various
         * reasons and purposes.
         */
        // Menu(AppHandler* currentAppHandler);

        /**
         * @brief 
         * Updates the menu. Redraws the screen if necessary
         * Handles the keyboard etc.
         * @return true 
         * @return false 
         */
        virtual bool Update() = 0;

        /**
         * @brief 
         * Call to draw the menu.
         * @return true 
         * @return false 
         */
        virtual bool Draw() = 0;

        /**
         * @brief 
         * Call to handle the keys pressed
         * and what they do in the application.
         * @param keyBoardKey 
         * @return true 
         * @return false 
         */
        virtual bool HandleKeyboard(int keyBoardKey) = 0;

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