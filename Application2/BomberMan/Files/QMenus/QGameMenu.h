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
#include "../Map/Map.h"
#include "../QObjects/QGameHeader.h"
#include "../QObjects/QMap.h"
#include "../QObjects/QPlayerStats.h"
#include "../Menus/Menu.h"

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
	void MapTileChanged(int x, int y, TileTypes newTile);
	void GameTimerChanged(uint64_t newTime);
	void CountDownValueChanged(int newValue);

	void PlayerHealthChanged(int playerID, int newHealth);
	void PlayerDied(int playerID);
	void PlayerSelectedNewInventorySlot(int playerID, int slotNumber);
	void PlayerInventoryChanged(int playerID);
	void PlayerDisconnected(int playerID);

	void GameStatusChanged(int newStatus);
	void PauseResumeButtonPressed();

private:

	void CreateTimers();
	void CreateWidgets();
	void CreateLayouts();
	void ConnectWidgets();
	void PutWidgetsInMenu();

	void SetAsPaused();
	void SetAsPlaying();
	void SetAsEnded();
	void SetAsCountdown();

	QMainWindow* winRef;
	AppHandler* appRef;

	QVBoxLayout*		MainLayout;
	QVBoxLayout*		TopLayout;
	QHBoxLayout*		BottomLayout;
	QGameHeader*		GameHeader;
	QBomberManMap*		GameMap;
	QPlayerStatsList*	PlayersStats;

	QWidget* MainMenu;
};