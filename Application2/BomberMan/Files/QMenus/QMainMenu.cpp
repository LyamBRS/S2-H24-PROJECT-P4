/**
 * @file MainMenu.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-04-05
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "QMainMenu.h"

// - CLASS - //
QMainMenu::QMainMenu()
{

}


QMainMenu::QMainMenu(QMainWindow* windowReference, AppHandler* appHandler)
{
	winRef = windowReference;
	appRef = appHandler;

	MainMenu = new QWidget();

	playButton		= new QPushButton("Play");
	settingsButton	= new QPushButton("Settings");
	appButton		= new QPushButton("Formulaire");
	leaveButton		= new QPushButton("Quit");

	connect(playButton,		&QPushButton::clicked, this, &QMainMenu::GoToMapSelection);
	connect(settingsButton, &QPushButton::clicked, this, &QMainMenu::GoToSettings);
	connect(appButton,		&QPushButton::clicked, this, &QMainMenu::GoToFormulaire);
	connect(leaveButton,	&QPushButton::clicked, this, &QMainMenu::GoToExit);

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

	if (GetAllMaps().size() == 0)
	{
		playButton->setEnabled(false);
		playButton->setText("NO MAPS FOUND");
	}
}

QWidget* QMainMenu::GetMenu()
{
	return MainMenu;
}

void QMainMenu::OnEnter()
{

}

void QMainMenu::OnLeave()
{

}



void QMainMenu::GoToSettings()
{
	appRef->SetNewQMenu(QMenus::Settings);
}

void QMainMenu::GoToMapSelection()
{
	appRef->SetNewQMenu(QMenus::PlayerJoining);
}

void QMainMenu::GoToFormulaire()
{
	appRef->SetNewQMenu(QMenus::Formulaire);
}

void QMainMenu::GoToExit()
{
	appRef->SetNewQMenu(QMenus::ExitMenu);
}