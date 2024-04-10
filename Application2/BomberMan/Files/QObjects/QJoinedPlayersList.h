/**
 * @file QJoinedPlayersList.h
 * @author LyamBRS
 * @brief
 * @version 0.1
 * @date 2024-04-09
 * @copyright Copyright (c) 2024
 */

#pragma once

 // - INCLUDES - //
#include <QtWidgets>
#include <vector>
#include "../Application/AppHandler.h"
#include "../Player/Player.h"

// - DEFINES - //

// - CLASS - //
class QJoinedPlayersSlot : public QObject
{
	Q_OBJECT
public:
	QJoinedPlayersSlot(int slotID);
	QWidget* GetWidget();

	void Set(bool used, int realWorldControllerID);

private:
	QWidget* MainWidget;
	QHBoxLayout* MainLayout;
	QLabel* PlayerID;
	QLabel* TypeOfController;
	QLabel* PlayerIcon;
};


class QJoinedPlayersList : public QObject
{
	Q_OBJECT
	
public:
	QJoinedPlayersList(int amountOfSlots);

	QWidget* GetWidget();

public slots:
	void EventUpdateSlot(int slotIndex, int realWorldControllerID);

private:

	QPushButton* backgroundButton;
	QVBoxLayout* MainLayout;

	std::vector<QJoinedPlayersSlot> playerSlots;

	QWidget* MainWidget;
};