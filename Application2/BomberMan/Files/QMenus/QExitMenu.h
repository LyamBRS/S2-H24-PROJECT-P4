/**
 * @file QExitMenu.h
 * @author LyamBRS
 * @brief
 * @version 0.1
 * @date 2024-04-05
 * @copyright Copyright (c) 2024
 */

#pragma once

 // - INCLUDES - //
#include <QtWidgets>
#include <QApplication>
#include "../Application/AppHandler.h"

// - DEFINES - //

// - CLASS - //

class QExitMenu : public QObject
{

public:
	QExitMenu();
	QExitMenu(QMainWindow* windowReference, AppHandler* appHandler);

	QWidget* GetMenu();

	void OnEnter();
	void OnLeave();

public slots:
	void GoToMainMenu();
	void LeaveApp();

private:

	void CreateWidgets();
	void ConnectWidgets();
	void CreateMenu();

	QMainWindow* winRef;
	AppHandler* appRef;

	QPushButton* LeaveAppButton;
	QPushButton* GoBackButton;
	QLabel* AreYouSureLabel;

	QGridLayout* MainLayout;

	QWidget* MainMenu;
};