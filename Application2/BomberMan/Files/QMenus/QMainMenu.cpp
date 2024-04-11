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

	QFont titleFont("Courier", 32, QFont::Bold, false);
	QFont btnFont("Courier", 24, QFont::Bold, false);
	QFont basicFont("Courier", 12, QFont::Bold, false);
	QApplication::setFont(basicFont);
	
	MainMenu = new QWidget();
	
	lblLogo = new QLabel();
	lblTeam = new QLabel("P4 Present");
	lblProjName = new QLabel("Bomber-Man");

	lblTeam->setFont(titleFont);
	lblProjName->setFont(titleFont);

	playButton		= new QPushButton("Play");
	playButton->setFont(btnFont);
	settingsButton	= new QPushButton("Settings");
	settingsButton->setFont(btnFont);
	appButton		= new QPushButton("Formulaire");
	appButton->setFont(btnFont);
	leaveButton		= new QPushButton("Quit");
	leaveButton->setFont(btnFont);

	connect(playButton,		&QPushButton::clicked, this, &QMainMenu::GoToMapSelection);
	connect(settingsButton, &QPushButton::clicked, this, &QMainMenu::GoToSettings);
	connect(appButton,		&QPushButton::clicked, this, &QMainMenu::GoToFormulaire);
	connect(leaveButton,	&QPushButton::clicked, this, &QMainMenu::GoToExit);

	MainLayout		= new QVBoxLayout();
	ButtonLogoLayout	= new QHBoxLayout();
	ButtonLayout = new QVBoxLayout();
	layTitle		= new QHBoxLayout();
	
	layTitle->addStretch();
	layTitle->addWidget(lblTeam);
	layTitle->addStretch();
	layTitle->addWidget(lblProjName);
	layTitle->addStretch();

	ButtonLayout->setAlignment(Qt::AlignLeft);
	ButtonLayout->addSpacing(75);
	ButtonLayout->addWidget(playButton);
	ButtonLayout->addWidget(appButton);
	ButtonLayout->addWidget(settingsButton);
	ButtonLayout->addStretch();
	ButtonLayout->addWidget(leaveButton);



	
	quint32 r = QRandomGenerator::global()->bounded(0, 200);
	quint32 g = QRandomGenerator::global()->bounded(0, 200);
	quint32 b = QRandomGenerator::global()->bounded(0, 200);
	QPixmap pm(ChangeSVGColor("Logo", QColor(r,g,b)));
	auto newPixmap = pm.scaled(500, 500);
	lblLogo->setPixmap(newPixmap);

	ButtonLogoLayout->addLayout(ButtonLayout);
	ButtonLogoLayout->addStretch();
	ButtonLogoLayout->addWidget(lblLogo);
	ButtonLogoLayout->addStretch();

	MainLayout->addLayout(layTitle);
	MainLayout->addLayout(ButtonLogoLayout);
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
	appRef->SetNewQMenu(QMenus::MapSelection);
}

void QMainMenu::GoToFormulaire()
{
	appRef->SetNewQMenu(QMenus::Formulaire);
}

void QMainMenu::GoToExit()
{
	appRef->SetNewQMenu(QMenus::ExitMenu);
}