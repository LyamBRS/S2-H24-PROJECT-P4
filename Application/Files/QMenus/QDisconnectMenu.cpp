/**
 * @file QDisconnectMenu.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-04-08
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "QDisconnectMenu.h"

// - CLASS - //
QDisconnectMenu::QDisconnectMenu()
{

}

QDisconnectMenu::QDisconnectMenu(QMainWindow* windowReference, AppHandler* appHandler)
{
	winRef = windowReference;
	appRef = appHandler;

	MainMenu = new QWidget();

	backButton		= new QPushButton("Back");
	//playButton->setMaximumWidth(200);
	//settingsButton->setMaximumWidth(200);
	//appButton->setMaximumWidth(200);
	//leaveButton->setMaximumWidth(200);

	MainLayout		= new QVBoxLayout();
	ButtonLayout	= new QVBoxLayout();
	
	ButtonLayout->setAlignment(Qt::AlignCenter);
	ButtonLayout->addWidget(backButton);

	MainLayout->addLayout(ButtonLayout);
	MainMenu->setLayout(MainLayout);
}

QWidget* QDisconnectMenu::GetMenu()
{
	return MainMenu;
}

void QDisconnectMenu::OnEnter()
{

}

void QDisconnectMenu::OnLeave()
{

}


void QDisconnectMenu::GoToMainMenu()
{
	appRef->SetNewQMenu(QMenus::MainMenu);
}