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
#include "../Colour/Colour.h"
#include "../SimpleTimer/SimpleTimer.h"
#include "../Serial/PortDetector.h"
#include <conio.h>
#include <vector>

// - DEFINES - //
#define APP_MAIN_MENU 0
#define APP_GAME_MENU 3
#define APP_TEST_MENU 1
#define APP_EXIT_MENU 4

#define APP_ARDUINO_MENU 2
#define APP_BAUD_RATE_MENU 5
#define APP_COM_PORT_MENU 6
#define APP_CONNECTING_MENU 7
#define APP_DISCONNECTING_MENU 8

#define KB_UP 72
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77
#define KB_ESCAPE 27
#define KB_ENTER 13

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

        SimpleTimer frameTimer = SimpleTimer(10);

        int wantedSelectedMenu = 1;
        int currentSelectedMenu = 0;

        int selection = 0;

        int oldAmountOfComPorts = 0;

        bool requiresNewDrawing = true;

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
         * Draws the little prompt which asks the user
         * if they really want to leave the application.
         * @return true 
         * @return false 
         */
        bool DrawExitMenu();

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

        /**
         * @brief 
         * Draws the menu that allows the user to select
         * a wanted com port as well as a wanted baud rate
         * and see if their connection was successful or not.
         * @return true 
         * @return false 
         */
        bool DrawArduinoSetupMenu();
        bool DrawArduinoBaudRateMenu();
        bool DrawArduinoComPortMenu();
        bool DrawArduinoConnectingMenu();
        bool DrawArduinoDisconnectingMenu();

        /**
         * @brief 
         * Handles all the drawing of all the menus
         * Specifies if they need to be redrawn as well.
         * @return true 
         * @return false 
         */
        bool HandleMenuDrawings();

        /**
         * @brief 
         * Handles the keyboard's keys when the current
         * menu is the main menu, allowing the selected
         * wanted menu to move up and down on the screen
         * and a selection to be selected through the
         * enter key.
         * @return true:
         * Handled a key 
         * @return false:
         * Wrong key / No keys?
         */
        bool MainMenuKeyboardHandler();

        /**
         * @brief 
         * Handles the keyboard's keys when the current
         * menu is the exit application menu, allowing
         * the user to answer a simple yes or no question
         * prompting him if he wants to leave the app or
         * not. Pressing enter while selecting the yes
         * option will make the application exit.
         * @return true:
         * Handled a key 
         * @return false:
         * Wrong key / No keys?
         */
        bool ExitMenuKeyboardHandler();

        /**
         * @brief 
         * Handles the keyboard's keys when the current
         * menu is the pre-game menu, allowing the user
         * to navigate and select a map that they want
         * to play.
         * @return true:
         * Handled a key 
         * @return false:
         * Wrong key / No keys?
         */
        bool GameMenuKeyboardHandler();

        /**
         * @brief 
         * Handles the keyboard's keys when the current
         * menu is the test menu, allowing the user to
         * test specific components of the application
         * through the terminal.
         * @return true:
         * Handled a key 
         * @return false:
         * Wrong key / No keys?
         */
        bool TestMenuKeyboardHandler();

        /**
         * @brief 
         * Handles the keyboard's keys when the current
         * menu is the arduino setup menu, allowing the
         * user to select a communication port, select
         * a BAUD rate and try to connect to an arduino.
         * Also displays the result of that communication
         * attempt and if data is received or not.
         * @return true:
         * Handled a key 
         * @return false:
         * Wrong key / No keys?
         */
        bool ArduinoSetupKeyboardHandler();

        bool ArduinoBaudRateKeyboardHandler();
        bool ArduinoComPortKeyboardHandler();
        bool ArduinoConnectingKeyboardHandler();
        bool ArduinoDisconnectingKeyboardHandler();

        /**
         * @brief 
         * Simple function which handles the arrow keys
         * of the user as well as the enter key so that
         * navigation is possible between menus.
         * @return true:
         * Successfully handled a valid key.
         * @return false:
         * Invalid key.
         */
        bool HandleKeyboardActions();
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