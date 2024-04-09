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
	LeaveAppButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	GoBackButton	= new QPushButton("Cancel");
	GoBackButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	AreYouSureLabel = new QLabel("Are you sure you want to quit this application?");
	AreYouSureLabel->setStyleSheet("border: 1px solid black;");
	AreYouSureLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	AreYouSureLabel->setAlignment(Qt::AlignCenter);

	MainLayout = new QGridLayout();
	MainLayout->setColumnStretch(0, 1);
	MainLayout->setColumnStretch(1, 1);
	MainLayout->setRowStretch(0, 1);
	MainLayout->setRowStretch(1, 1);
}

void QExitMenu::ConnectWidgets()
{
	connect(LeaveAppButton, &QPushButton::clicked, this, &QExitMenu::LeaveApp);
	connect(GoBackButton, &QPushButton::clicked, this, &QExitMenu::GoToMainMenu);
}

void QExitMenu::CreateMenu()
{
	MainLayout->addWidget(AreYouSureLabel, 0, 0, 1, 2);
	MainLayout->addWidget(GoBackButton, 1, 0, 2, 1);
	MainLayout->addWidget(LeaveAppButton, 1, 1, 2, 1);

	MainMenu->setLayout(MainLayout);
}





void QExitMenu::GoToMainMenu()
{
	appRef->SetNewQMenu(QMenus::MainMenu);
}

void QExitMenu::LeaveApp()
{
	qApp->exit();
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