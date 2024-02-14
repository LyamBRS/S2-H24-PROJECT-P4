/**
 * @file Application.cpp
 * @author LyamBRS
 * @brief
 * File containing the basic test
 * application program of the
 * Application.
 * @version 0.1
 * @date 2024-02-14
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "Application.h"

// - PROGRAM - //
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
bool Application::DrawMainMenu()
{
    return false;
}

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
bool Application::DrawCommTestMenu()
{
    return false;
}

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
bool Application::DrawGameMenu()
{
    return false;
}

/**
 * @brief
 * # Application
 * @brief
 * Class used to create one application.
 * The application allow you to setup your Arduino
 * and setup your game. It handles basic terminal
 * menus as well.
 */
Application::Application()
{

}

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
bool Application::Update()
{
    arduino.Update();
    currentGame.Update();
    return true;
}

/**
 * @brief 
 * Debug loop executed until the terminal
 * application wants to close.
 */
void Application::TemporaryLoop()
{
    while(wantedSelectedMenu != -1)
    {
        Sleep(100);
        Update();
    }
}