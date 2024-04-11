/**
 * @file QPlayerJoiningMenu.h
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

#include "../QObjects/QJoinedPlayersList.h"

// - DEFINES - //

// - CLASS - //

class QPlayerJoiningMenu : public QObject
{

public:
	QPlayerJoiningMenu();
	QPlayerJoiningMenu(QMainWindow* windowReference, AppHandler* appHandler);

	QWidget* GetMenu();

	void OnEnter();
	void OnLeave();

	void CreateTimers();
	void CreateWidgets();
	void CreateLayouts();
	void ConnectWidgets();
	void CreateMenu();
	void CreateGame();

public slots:
	void CancelPressed();
	void StartGamePressed();
	void PlayerCountChanged(int newPlayerCount);

	void PlayerConnected(int playerID, int realWorldControllerID);
	void PlayerDisconnected(int playerID);

private:

	QMainWindow* winRef;
	AppHandler* appRef;

	QGridLayout* MainLayout;

	QLabel* WaitingForPlayersToJoinLabel;
	QProgressBar* JoinedPlayersProgress;

	QJoinedPlayersList* JoinedPlayersList;

	QPushButton* CancelButton;
	QPushButton* StartGameButton;

	QWidget* MainMenu;
};