/**
 * @file Handler.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-04-08
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "Handler.h"
// - DEFINES - //

// - PROGRAM - //

QMenuHandler::QMenuHandler(QMainWindow* windowReference, AppHandler* appHandler)
{
    winRef = windowReference;
    appRef = appHandler;

    mainMenu = new QMainMenu(windowReference, appRef);
    winRef->setCentralWidget(mainMenu->GetMenu());
    mainMenu->OnEnter();
}

void QMenuHandler::GoToMenu(int menuIndex)
{
    LeaveCurrent();
    currentMenu = menuIndex;

    switch(menuIndex)
    {
        case(QMenus::MainMenu):
            mainMenu = new QMainMenu(winRef, appRef);
            winRef->setCentralWidget(mainMenu->GetMenu());
            break;

        case(QMenus::MapSelection):
            mapSelectionMenu = new QMapSelectionMenu(winRef, appRef);
            winRef->setCentralWidget(mapSelectionMenu->GetMenu());
            break;

        case(QMenus::PlayerJoining):
            playerJoiningMenu = new QPlayerJoiningMenu(winRef, appRef);
            winRef->setCentralWidget(playerJoiningMenu->GetMenu());
            break;

        case(QMenus::Countdown):
            countDownMenu = new QCountDownMenu(winRef, appRef);
            winRef->setCentralWidget(countDownMenu->GetMenu());
            break;

        case(QMenus::Game):
            gameMenu = new QGameMenu(winRef, appRef);
            winRef->setCentralWidget(gameMenu->GetMenu());
            break;

        case(QMenus::PauseMenu):
            pauseMenu = new QPauseMenu(winRef, appRef);
            winRef->setCentralWidget(pauseMenu->GetMenu());
            break;

        case(QMenus::ExitMenu):
            exitMenu = new QExitMenu(winRef, appRef);
            winRef->setCentralWidget(exitMenu->GetMenu());
            break;

        case(QMenus::Formulaire):
            formulaire = new QFormulaire(winRef, appRef);
            winRef->setCentralWidget(formulaire->GetMenu());
            break;

        case(QMenus::Settings):
            settings = new QSettingsMenu(winRef, appRef);
            winRef->setCentralWidget(settings->GetMenu());
            break;

        case(QMenus::Disconnect):
            disconnectMenu = new QDisconnectMenu(winRef, appRef);
            winRef->setCentralWidget(disconnectMenu->GetMenu());
            break;

        case(QMenus::Error):
            break;
    }
    OnEnterCurrent();
}

void QMenuHandler::LeaveCurrent()
{
    switch(currentMenu)
    {
        case(QMenus::MainMenu):
            mainMenu->OnLeave();
            return;

        case(QMenus::MapSelection):
            mapSelectionMenu->OnLeave();
            return;

        case(QMenus::PlayerJoining):
            playerJoiningMenu->OnLeave();
            return;

        case(QMenus::Countdown):
            countDownMenu->OnLeave();
            return;

        case(QMenus::Game):
            gameMenu->OnLeave();
            return;

        case(QMenus::PauseMenu):
            pauseMenu->OnLeave();
            return;

        case(QMenus::ExitMenu):
            exitMenu->OnLeave();
            return;

        case(QMenus::Formulaire):
            formulaire->OnLeave();
            return;

        case(QMenus::Settings):
            settings->OnLeave();
            return;

        case(QMenus::Disconnect):
            disconnectMenu->OnLeave();
            return;

        case(QMenus::Error):
            return;
    }
}

void QMenuHandler::OnEnterCurrent()
{
    switch(currentMenu)
    {
        case(QMenus::MainMenu):
            mainMenu->OnEnter();
            return;

        case(QMenus::MapSelection):
            mapSelectionMenu->OnEnter();
            return;

        case(QMenus::PlayerJoining):
            playerJoiningMenu->OnEnter();
            return;

        case(QMenus::Countdown):
            countDownMenu->OnEnter();
            return;

        case(QMenus::Game):
            gameMenu->OnEnter();
            return;

        case(QMenus::PauseMenu):
            pauseMenu->OnEnter();
            return;

        case(QMenus::ExitMenu):
            exitMenu->OnEnter();
            return;

        case(QMenus::Formulaire):
            formulaire->OnEnter();
            return;

        case(QMenus::Settings):
            settings->OnEnter();
            return;

        case(QMenus::Disconnect):
            disconnectMenu->OnEnter();
            return;

        case(QMenus::Error):
            return;
    }
}