/**
 * @file QSettingsMenu.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-04-08
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "QSettingsMenu.h"

// - CLASS - //
QSettingsMenu::QSettingsMenu()
{

}

QSettingsMenu::QSettingsMenu(QMainWindow* windowReference, AppHandler* appHandler)
{
	winRef = windowReference;
	appRef = appHandler;

	MainMenu = new QWidget();

	backButton		= new QPushButton("Back");
	connect(backButton, &QPushButton::clicked, this, &QSettingsMenu::GoToMainMenu);
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

QWidget* QSettingsMenu::GetMenu()
{
	return MainMenu;
}

void QSettingsMenu::OnEnter()
{

}

void QSettingsMenu::OnLeave()
{

}


void QSettingsMenu::GoToMainMenu()
{
	appRef->SetNewQMenu(QMenus::MainMenu);
}