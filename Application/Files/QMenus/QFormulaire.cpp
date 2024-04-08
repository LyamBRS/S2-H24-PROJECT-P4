/**
 * @file QSettingsMenu.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-04-08
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "QFormulaire.h"

// - CLASS - //
QFormulaire::QFormulaire()
{

}

QFormulaire::QFormulaire(QMainWindow* windowReference, AppHandler* appHandler)
{
	winRef = windowReference;
	appRef = appHandler;

	MainMenu = new QWidget();

	playButton		= new QPushButton("lll");
	settingsButton	= new QPushButton("lll");
	appButton		= new QPushButton("Formulaire");
	leaveButton		= new QPushButton("lll");

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

QWidget* QFormulaire::GetMenu()
{
	return MainMenu;
}

void QFormulaire::OnEnter()
{

}

void QFormulaire::OnLeave()
{

}