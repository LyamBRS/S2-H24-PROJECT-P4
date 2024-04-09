/**
 * @file QPauseMenu.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-04-05
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "QPauseMenu.h"

// - CLASS - //
QPauseMenu::QPauseMenu()
{

}


QPauseMenu::QPauseMenu(QMainWindow* windowReference, AppHandler* appHandler)
{
	winRef = windowReference;
	appRef = appHandler;

	MainMenu = new QWidget();

	playButton		= new QPushButton("Play");
	settingsButton	= new QPushButton("Settings");
	appButton		= new QPushButton("Formulaire");
	leaveButton		= new QPushButton("Quit");

	MainLayout		= new QVBoxLayout();
	ButtonLayout	= new QVBoxLayout();
	
	ButtonLayout->setAlignment(Qt::AlignCenter);
	ButtonLayout->addWidget(playButton);
	ButtonLayout->addWidget(appButton);
	ButtonLayout->addWidget(settingsButton);
	ButtonLayout->addSpacing(100);
	ButtonLayout->addWidget(leaveButton);

	MainLayout->addLayout(ButtonLayout);
	MainMenu->setLayout(MainLayout);
}

QWidget* QPauseMenu::GetMenu()
{
	return MainMenu;
}

void QPauseMenu::OnEnter()
{

}

void QPauseMenu::OnLeave()
{

}

void QPauseMenu::GoToSettings()
{
	std::cout << "GO TO SETTINGS" << std::endl;
	appRef->SetNewQMenu(QMenus::Settings);
}