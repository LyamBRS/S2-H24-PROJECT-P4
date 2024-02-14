/**
 * @file Application.h
 * @author LyamBRS
 * @brief
 * Header file for the definition of the Application
 * class which is used to handle the application on
 * the Backend level of things.
 * @version 0.1
 * @date 2024-02-14
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include "../Arduino/Arduino.h"
#include "../Game/Game.h"

// - DEFINES - //
#define APP_MAIN_MENU 0
#define APP_GAME_MENU 1
#define APP_TEST_MENU 2

// - CLASS - //

/**
 * @brief
 * # Application
 * @brief
 * Class used to create one application.
 * The application allow you to setup your Arduino
 * and setup your game. It handles basic terminal
 * menus as well.
 */
class Application
{
    private:
        Arduino arduino;
        Game currentGame;

        int wantedSelectedMenu = 0;
        int currentSelectedMenu = 0;

        /**
         * @brief 
         * Draws a simple main menu where the user can
         * select what they want to do by pressing a
         * number on their terminal.
         * @return true:
         * Successfully drew the main menu.
         * @return false:
         * Failed to draw the main menu.
         */
        bool DrawMainMenu();

        /**
         * @brief 
         * Draw the arduino communication test menu
         * where the user can see what their Arduino
         * is answering to a handshake request by
         * printing JSON on the terminal.
         * @return true:
         * Successfully drew communication test
         * menu.
         * @return false:
         * Failed to draw communication test menu. 
         */
        bool DrawCommTestMenu();

        /**
         * @brief 
         * Draw the menu where the user can select which
         * map they want to play to eventually start the
         * game so that they can play it.
         * @return true:
         * Successfully drew the game menu.
         * @return false:
         * Failed to draw the game menu.
         */
        bool DrawGameMenu();
    public:

        /**
         * @brief
         * # Application
         * @brief
         * Class used to create one application.
         * The application allow you to setup your Arduino
         * and setup your game. It handles basic terminal
         * menus as well.
         */
        Application();

        /**
         * @brief 
         * Updates the application each QT frames.
         * Calls all the Update functions of all the
         * things in the application.
         * @return true:
         * Successfully updated all the application.
         * @return false:
         * Failed to update all the application.
         */
        bool Update();

        /**
         * @brief 
         * Debug loop executed until the terminal
         * application wants to close.
         */
        void TemporaryLoop();
};