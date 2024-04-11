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
Application::Application(QMainWindow* windowReference)
{
    auto lambda = [this](int newIndex) { this->SetNewQMenu(newIndex); };
    appHandler = new AppHandler(lambda);

    appHandler->currentGame = new BomberManGame();

    appHandler->colorPlayerA = new QColor("#4a4aed");
    appHandler->colorPlayerB = new QColor("#eb3d3d");
    appHandler->colorPlayerC = new QColor("c2be4a");
    appHandler->colorPlayerD = new QColor("41d146");
    appHandler->colorPlayerE = new QColor("8000FF");

    // Creates all the menus.
    cMenu* exitMenu      = new cExitMenu(appHandler);
    cMenu* arduinoMenu   = new cArduinoMenu(appHandler);
    cMenu* mainMenu      = new cMainMenu(appHandler);
    cMenu* mapMenu       = new cMapMenu(appHandler);
    cMenu* testMenu      = new cTestMenu(appHandler);
    cMenu* gameMenu      = new cGameMenu(appHandler);

    menus.push_back(mainMenu);
    menus.push_back(testMenu);
    menus.push_back(arduinoMenu);
    menus.push_back(mapMenu);
    menus.push_back(exitMenu);
    menus.push_back(gameMenu);

    menuHandler = new QMenuHandler(windowReference, appHandler);
}

Application::Application()
{

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
        int character = getch();
        appHandler->requiresNewDrawing = appHandler->redrawOnKeyboardHits;
        return menus[appHandler->currentSelectedMenu]->HandleKeyboard(character);
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
    if(appHandler->requiresNewDrawing)
    {
        appHandler->requiresNewDrawing = false;
        return menus[appHandler->currentSelectedMenu]->Draw();
    }
    return true;
}

/**
 * @brief 
 * Simple function which handles the generic update
 * functions of the currently selected menu.
 * @return true:
 * Successfully updated the current menu
 * @return false:
 * Failed to update the current menu
 */
bool Application::HandleMenuUpdates()
{
    return menus[appHandler->currentSelectedMenu]->Update();
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
    static int oldSelectedMenu = 0;
    static int oldAmountOfComPort = 0;

    // Allows you to immediately see if a COM port change occurs
    if(appHandler->oldAmountOfComPorts != GetAvailableComPorts().size())
    {
       appHandler->oldAmountOfComPorts = (int)GetAvailableComPorts().size();
       appHandler->requiresNewDrawing = true;
    }

    //HandleMenuDrawings();
    HandleKeyboardActions();
    HandleMenuUpdates();

    appHandler->currentGame->Update();

    if(oldSelectedMenu != appHandler->currentSelectedMenu)
    {
        menus[oldSelectedMenu]->OnExit();
        menus[appHandler->currentSelectedMenu]->OnEnter();
        oldSelectedMenu = appHandler->currentSelectedMenu;
    }

    //appHandler.arduinoThread.threadFunction(0);
    appHandler->arduinoThread.GetArduino()->Update();

    if(appHandler->frameTimer.TimeLeft() == 0)
    {
        appHandler->UpdateKeyboardControllers();
    }

    if (MiscUpdateTimer.TimeLeft() == 0)
    {
        appHandler->amountOfAvailablePorts = (int)GetAvailableComPorts().size();

        if (oldAmountOfComPort != appHandler->amountOfAvailablePorts)
        {
            oldAmountOfComPort = appHandler->amountOfAvailablePorts;
        }
    }

    //if(!appHandler.arduinoThread.GetThreadStatus())
    //{
    //   //std::cout << std::endl;
    //   //std::cout << "THREAD IS NO LONGER LIVING" << std::endl;
    //}

    return true;
}

/**
 * @brief 
 * Debug loop executed until the terminal
 * application wants to close.
 */
void Application::TemporaryLoop()
{
    while(appHandler->wantedSelectedMenu != -1)
    {
        if(!Update())
        {
            return;
        }
    }
}

AppHandler* Application::GetHandler()
{
    return appHandler;
}

void Application::SetNewQMenu(int newMenu)
{
    menuHandler->GoToMenu(newMenu);
}