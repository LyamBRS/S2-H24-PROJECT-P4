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
QSettingsMenu::QSettingsMenu(QMainWindow* windowReference)
{
	winRef = windowReference;

	MainMenu = new QWidget();

	playButton		= new QPushButton("Play");
	settingsButton	= new QPushButton("Settings");
	appButton		= new QPushButton("Formulaire");
	leaveButton		= new QPushButton("Quit");

	//playButton->setMaximumWidth(200);
	//settingsButton->setMaximumWidth(200);
	//appButton->setMaximumWidth(200);
	//leaveButton->setMaximumWidth(200);

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

QMainWindow* QSettingsMenu::GetWindow()
{
	return winRef;
}

void QSettingsMenu::OnEnter()
{
	winRef->setCentralWidget(MainMenu);
}

void QSettingsMenu::OnLeave()
{

}