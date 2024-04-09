/**
 * @file QMapSelectionMenu.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-04-05
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "QMapSelectionMenu.h"

// - CLASS - //
QMapSelectionMenu::QMapSelectionMenu()
{

}


QMapSelectionMenu::QMapSelectionMenu(QMainWindow* windowReference, AppHandler* appHandler)
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

QWidget* QMapSelectionMenu::GetMenu()
{
	return MainMenu;
}

void QMapSelectionMenu::OnEnter()
{

}

void QMapSelectionMenu::OnLeave()
{

}

void QMapSelectionMenu::GoToSettings()
{
	std::cout << "GO TO SETTINGS" << std::endl;
	appRef->SetNewQMenu(QMenus::Settings);
}