/**
 * @file QSettingsMenu.h
 * @author LyamBRS
 * @brief
 * @version 0.1
 * @date 2024-04-08
 * @copyright Copyright (c) 2024
 */

#pragma once

 // - INCLUDES - //
#include <QWidget>
#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>
#include <qmenubar.h>
#include "../Application/AppHandler.h"

// - DEFINES - //

// - CLASS - //

class QSettingsMenu : public QObject
{
private:

	QMainWindow* winRef;
	AppHandler* appRef;

	QPushButton* backButton;

	QVBoxLayout* MainLayout;
	QVBoxLayout* ButtonLayout;

	QWidget* MainMenu;

public:
	QSettingsMenu();
	QSettingsMenu(QMainWindow* windowReference, AppHandler* appHandler);

	QWidget* GetMenu();

	void OnEnter();
	void OnLeave();

public slots:
	void GoToMainMenu();
};