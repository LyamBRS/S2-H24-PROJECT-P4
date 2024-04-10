/**
 * @file QGameMenu.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-04-05
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "QGameMenu.h"

// - CLASS - //
QGameMenu::QGameMenu()
{

}


QGameMenu::QGameMenu(QMainWindow* windowReference, AppHandler* appHandler)
{
	winRef = windowReference;
	appRef = appHandler;

	//MainMenu = new QWidget();
	//
	//playButton		= new QPushButton("Play");
	//settingsButton	= new QPushButton("Settings");
	//appButton		= new QPushButton("Formulaire");
	//leaveButton		= new QPushButton("Quit");
	//
	//MainLayout		= new QVBoxLayout();
	//ButtonLayout	= new QVBoxLayout();
	//
	//ButtonLayout->setAlignment(Qt::AlignCenter);
	//ButtonLayout->addWidget(playButton);
	//ButtonLayout->addWidget(appButton);
	//ButtonLayout->addWidget(settingsButton);
	//ButtonLayout->addSpacing(100);
	//ButtonLayout->addWidget(leaveButton);
	//
	//MainLayout->addLayout(ButtonLayout);
	//MainMenu->setLayout(MainLayout);
}





void QGameMenu::CreateTimers()
{

}

void QGameMenu::CreateWidgets()
{

}

void QGameMenu::CreateLayouts()
{

}

void QGameMenu::ConnectWidgets()
{

}

void QGameMenu::PutWidgetsInMenu()
{

}

















QWidget* QGameMenu::GetMenu()
{
	return MainMenu;
}

void QGameMenu::OnEnter()
{
	// Check if the current game's status is that of the playing game.
	switch (appRef->currentGame->GetStatus())
	{
		case(GameStatuses::awaitingConnection):
			break;
	
		case(GameStatuses::awaitingPlayers):
			appRef->SetNewQMenu(QMenus::PlayerJoining);
			break;
	
		case(GameStatuses::ended):
			break;
	
		case(GameStatuses::countdown):
			appRef->SetNewQMenu(QMenus::Countdown);
			break;
	
		case(GameStatuses::invalid):
			appRef->SetNewQMenu(QMenus::Error);
			break;
	
		case(GameStatuses::paused):
			appRef->SetNewQMenu(QMenus::PauseMenu);
			break;
	
		case(GameStatuses::playing):
			// We're good!
			break;
	}
}

void QGameMenu::OnLeave()
{

}