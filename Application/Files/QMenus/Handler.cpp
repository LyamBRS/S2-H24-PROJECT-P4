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
    settings = new QSettingsMenu(windowReference, appRef);
    formulaire = new QFormulaire(windowReference, appRef);

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
            break;

        case(QMenus::PlayerJoining):
            break;

        case(QMenus::Countdown):
            break;

        case(QMenus::Game):
            break;

        case(QMenus::PauseMenu):
            break;

        case(QMenus::ExitMenu):
            break;

        case(QMenus::Formulaire):
            formulaire = new QFormulaire(winRef, appRef);
            winRef->setCentralWidget(formulaire->GetMenu());
            break;

        case(QMenus::Settings):
            settings = new QSettingsMenu(winRef, appRef);
            winRef->setCentralWidget(settings->GetMenu());
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
            return;

        case(QMenus::PlayerJoining):
            return;

        case(QMenus::Countdown):
            return;

        case(QMenus::Game):
            return;

        case(QMenus::PauseMenu):
            return;

        case(QMenus::ExitMenu):
            return;

        case(QMenus::Formulaire):
            formulaire->OnLeave();
            return;

        case(QMenus::Settings):
            settings->OnLeave();
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
            return;

        case(QMenus::PlayerJoining):
            return;

        case(QMenus::Countdown):
            return;

        case(QMenus::Game):
            return;

        case(QMenus::PauseMenu):
            return;

        case(QMenus::ExitMenu):
            return;

        case(QMenus::Formulaire):
            formulaire->OnEnter();
            return;

        case(QMenus::Settings):
            settings->OnEnter();
            return;

        case(QMenus::Error):
            return;
    }
}