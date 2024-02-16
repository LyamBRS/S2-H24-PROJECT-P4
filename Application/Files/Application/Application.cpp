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
 * # Application
 * @brief
 * Class used to create one application.
 * The application allow you to setup your Arduino
 * and setup your game. It handles basic terminal
 * menus as well.
 */
Application::Application()
{
    AppHandler* appHandlerPtr = &appHandler;

    // Creates all the menus.
    Menu* exitMenu      = new ExitMenu(appHandlerPtr);
    Menu* arduinoMenu   = new ArduinoMenu(appHandlerPtr);
    Menu* mainMenu      = new MainMenu(appHandlerPtr);
    Menu* mapMenu       = new MapMenu(appHandlerPtr);
    Menu* testMenu      = new TestMenu(appHandlerPtr);

    menus.push_back(mainMenu);
    menus.push_back(testMenu);
    menus.push_back(arduinoMenu);
    menus.push_back(mapMenu);
    menus.push_back(exitMenu);
}

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
bool Application::HandleKeyboardActions()
{
    if (kbhit())
    {
        appHandler.requiresNewDrawing = true;
        return menus[appHandler.currentSelectedMenu]->HandleKeyboard(getch());
    }
    return true;
}

/**
 * @brief 
 * Handles all the drawing of all the menus
 * Specifies if they need to be redrawn as well.
 * @return true 
 * @return false 
 */
bool Application::HandleMenuDrawings()
{
    if(appHandler.requiresNewDrawing)
    {
        appHandler.requiresNewDrawing = false;
        return menus[appHandler.currentSelectedMenu]->Draw();
    }
    return true;
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
    // Allows you to immediately see if a COM port change occurs
    if(appHandler.oldAmountOfComPorts != GetAvailableComPorts().size())
    {
       appHandler.oldAmountOfComPorts = GetAvailableComPorts().size();
       appHandler.requiresNewDrawing = true;
    }

    HandleMenuDrawings();
    HandleKeyboardActions();

    if(appHandler.frameTimer.TimeLeft() == 0)
    {
        appHandler.arduino.Update();
        appHandler.currentGame.Update();
    }
    return true;
}

/**
 * @brief 
 * Debug loop executed until the terminal
 * application wants to close.
 */
void Application::TemporaryLoop()
{
    while(appHandler.wantedSelectedMenu != -1)
    {
        Update();
    }
}