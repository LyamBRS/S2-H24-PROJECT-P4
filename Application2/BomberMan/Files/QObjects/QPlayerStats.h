/**
 * @file QCountDownMenu.h
 * @author LyamBRS
 * @brief
 * @version 0.1
 * @date 2024-04-05
 * @copyright Copyright (c) 2024
 */

#pragma once

 // - INCLUDES - //
#include <QtWidgets>
#include "../Application/AppHandler.h"
#include "../Player/Player.h"

// - DEFINES - //
#define INVENTORY_SVG_SCALE 20

// - CLASS - //

class QPlayerStat : public QWidget
{
	Q_OBJECT

	public:
		QPlayerStat(int playerID);

		void LinkPlayer(Player* player);

		void HealthChanged();
		void InventoryChanged();

	private:
		QVBoxLayout* MainLayout;
		QHBoxLayout* TopLayout;
		QHBoxLayout* BottomLayout;
		QLabel* PlayerNameLabel;
		QProgressBar* HealthProgressBar;

		QHBoxLayout* InventoryLayout;

		Player* playerRef;

		QVector<QLabel*> inventorySlots;
};

class QPlayerStatsList : public QWidget
{
	Q_OBJECT
	
public:
	QPlayerStatsList(int playerCount, BomberManGame* currentGame);
	void LinkPlayer(int playerID, Player* player);

public slots:
	void HealthEvent();
	void InventoryEvent();

private:
	int playerCountRef = 0;

	QVBoxLayout* mainLayout;
	QVector<QPlayerStat*> playerSlots;
};