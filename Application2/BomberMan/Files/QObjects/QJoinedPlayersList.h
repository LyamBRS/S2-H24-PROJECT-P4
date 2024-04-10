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
class QJoinedPlayersSlot : public QWidget
{
	Q_OBJECT
public:
	QJoinedPlayersSlot(int slotID);
	QWidget* GetWidget();

	void Set(bool used, int realWorldControllerID, QColor associatedColour);

	QWidget* MainWidget;
	QHBoxLayout* MainLayout;
	QLabel* PlayerID;
	QLabel* TypeOfController;
	QLabel* PlayerIcon;

	int playerID;
};


class QJoinedPlayersList : public QWidget
{
	Q_OBJECT
	
public:
	QJoinedPlayersList(int amountOfSlots);

	QWidget* GetWidget();

	void SetSlot(int slotIndex, bool used, int controllerType, QColor associatedColour);

	QVBoxLayout* MainLayout;
	QVector<QJoinedPlayersSlot*> playerSlots;
	QWidget* MainWidget;

public slots:
	void EventUpdateSlot(int slotIndex, int realWorldControllerID);
};