/**
 * @file MainMenu.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-04-05
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "QExitMenu.h"

// - CLASS - //
QExitMenu::QExitMenu()
{

}


QExitMenu::QExitMenu(QMainWindow* windowReference, AppHandler* appHandler)
{
	winRef = windowReference;
	appRef = appHandler;

	CreateWidgets();
	ConnectWidgets();
	CreateMenu();
}

void QExitMenu::CreateWidgets()
{
	MainMenu		= new QWidget();
	LeaveAppButton	= new QPushButton("Quit application");
	GoBackButton	= new QPushButton("Cancel");
	AreYouSureLabel = new QLabel("Are you sure you want to quit this application?");

	MainLayout = new QGridLayout();
}

void QExitMenu::ConnectWidgets()
{
	connect(LeaveAppButton, &QPushButton::clicked, this, &QExitMenu::LeaveApp);
	connect(GoBackButton, &QPushButton::clicked, this, &QExitMenu::GoToMainMenu);
}

void QExitMenu::CreateMenu()
{
	MainLayout->addWidget(AreYouSureLabel, 0, 0, 2, 1);
	MainLayout->addWidget(GoBackButton, 1, 0, 1, 1);
	MainLayout->addWidget(LeaveAppButton, 1, 1, 1, 1);

	MainMenu->setLayout(MainLayout);
}





void QExitMenu::GoToMainMenu()
{
	appRef->SetNewQMenu(QMenus::MainMenu);
}

void QExitMenu::LeaveApp()
{

}





QWidget* QExitMenu::GetMenu()
{
	return MainMenu;
}

void QExitMenu::OnEnter()
{

}

void QExitMenu::OnLeave()
{

}