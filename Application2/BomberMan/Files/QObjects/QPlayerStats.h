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

// - CLASS - //

class QPlayerStats : public QObject
{
	Q_OBJECT
	
public:
	QPlayerStats();

	QWidget* GetMenu();

	void OnEnter();
	void OnLeave();

public slots:
	void HealthEvent();
	void InventoryEvent();

private:
	AppHandler* appRef;
	Player* playerRef;

	QWidget* MainWidget;
};