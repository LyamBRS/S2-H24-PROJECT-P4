/**
 * @file Handler.h
 * @author LyamBRS
 * @brief 
 * Hosts the class which the Qapp uses to get
 * different menus and show the right one at
 * the right time.
 * Otherwise, we have circular imports. Yippie!
 * @version 0.1
 * @date 2024-04-05
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

#include "QMainMenu.h"
#include "QSettingsMenu.h"
#include "QFormulaire.h"
#include "QCountDownMenu.h"
#include "QPauseMenu.h"
#include "QGameMenu.h"
#include "QMapSelectionMenu.h"
#include "QPlayerJoiningMenu.h"
#include "QExitMenu.h"
#include "../Application/AppHandler.h"

// - DEFINES - //

// - CLASS - //

class QMenuHandler
{
    private:
        QMainWindow* winRef;
        AppHandler* appRef;

        QMainMenu* mainMenu;
        QFormulaire* formulaire;
        QSettingsMenu* settings;

        QCountDownMenu* countDownMenu;
        QPauseMenu* pauseMenu;
        QGameMenu* gameMenu;
        QMapSelectionMenu* mapSelectionMenu;
        QPlayerJoiningMenu* playerJoiningMenu;
        QExitMenu* exitMenu;

        int currentMenu = 0;

    public:

    QMenuHandler(QMainWindow* windowReference, AppHandler* appHandler);

    void GoToMenu(int menuIndex);
    void LeaveCurrent();
    void OnEnterCurrent();
};