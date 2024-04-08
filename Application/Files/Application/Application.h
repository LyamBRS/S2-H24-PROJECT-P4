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
#include <QtWidgets>
#include <QWidget>
#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>
#include <QApplication>
#include <QTimer>
#include <qmenubar.h>

#include "../Arduino/Arduino.h"
#include "../Game/Game.h"
#include "../Colour/Colour.h"
#include "../SimpleTimer/SimpleTimer.h"
#include "../Serial/PortDetector.h"
#include "AppHandler.h"
#include "../Menus/Menu.h"
#include "../Menus/ArduinoMenu.h"
#include "../Menus/ExitMenu.h"
#include "../Menus/MainMenu.h"
#include "../Menus/MapMenu.h"
#include "../Menus/TestMenu.h"
#include "../Menus/GameMenu.h"

#include "../QMenus/Handler.h"
#include "../QMenus/QFormulaire.h"
#include "../QMenus/QSettingsMenu.h"
#include "../QMenus/QMainMenu.h"

#include <conio.h>
#include <vector>

// - DEFINES - //

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
         * Simple function which handles the arrow keys
         * of the user as well as the enter key so that
         * navigation is possible between menus.
         * @return true:
         * Successfully handled a valid key.
         * @return false:
         * Invalid key.
         */
        bool HandleKeyboardActions();

        /**
         * @brief 
         * Simple function which handles the generic update
         * functions of the currently selected menu.
         * @return true:
         * Successfully updated the current menu
         * @return false:
         * Failed to update the current menu
         */
        bool HandleMenuUpdates();

        QMenuHandler* menuHandler;

        std::vector<cMenu*> menus;

    public:

        AppHandler* appHandler;

        /**
         * @brief
         * # Application
         * @brief
         * Class used to create one application.
         * The application allow you to setup your Arduino
         * and setup your game. It handles basic terminal
         * menus as well.
         */
        Application(QMainWindow* windowReference);

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

        AppHandler* GetHandler();

        void SetNewQMenu(int newMenu);
};