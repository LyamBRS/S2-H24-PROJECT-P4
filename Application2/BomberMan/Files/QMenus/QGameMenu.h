/**
 * @file QGameMenu.h
 * @author LyamBRS
 * @brief
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
#include "../Application/AppHandler.h"
#include "../Game/Game.h"

// - DEFINES - //

// - CLASS - //

class QGameMenu : public QObject
{

public:
	QGameMenu();
	QGameMenu(QMainWindow* windowReference, AppHandler* appHandler);

	QWidget* GetMenu();

	void OnEnter();
	void OnLeave();

public slots:
	void GoToSettings();

private:

	void CreateTimers();
	void CreateWidgets();
	void CreateLayouts();
	void ConnectWidgets();
	void CreateMenu();

	QMainWindow* winRef;
	AppHandler* appRef;

	QVBoxLayout* MainLayout;

	QWidget* MainMenu;
};