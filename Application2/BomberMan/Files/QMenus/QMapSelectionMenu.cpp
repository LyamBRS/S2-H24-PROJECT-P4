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

	btnLeave		= new QPushButton("Cancel");
	btnSelectionLeft = new QPushButton("<");
	btnPlay		= new QPushButton("Play");
	btnSelectionRight = new QPushButton(">");

	connect(btnLeave, &QPushButton::clicked, this, &QMapSelectionMenu::GoBack);
	connect(btnSelectionLeft, &QPushButton::clicked, this, &QMapSelectionMenu::SelectionPrevious);
	connect(btnSelectionRight, &QPushButton::clicked, this, &QMapSelectionMenu::SelectionNext);
	connect(btnPlay, &QPushButton::clicked, this, &QMapSelectionMenu::Play);

	lblMapSize = new QLabel("X, Y");
	lblNbPlayer = new QLabel("nb player");
	lblMapName = new QLabel("map name");

	layMain		= new QVBoxLayout();
	layButton	= new QHBoxLayout();
	layMapGrid	= new QGridLayout();
	layLabels	= new QHBoxLayout();
	
	layButton->setAlignment(Qt::AlignCenter);
	layButton->addWidget(btnSelectionLeft);
	layButton->addWidget(btnPlay);
	layButton->addWidget(btnSelectionRight);
	
	layLabels->setAlignment(Qt::AlignCenter);
	layLabels->addWidget(lblMapName);
	layLabels->addSpacing(20);
	layLabels->addWidget(lblMapSize);
	layLabels->addSpacing(20);
	layLabels->addWidget(lblNbPlayer);

	layMapGrid->setVerticalSpacing(2);
	layMapGrid->setHorizontalSpacing(2);

	
	
	layMain->addLayout(layLabels);
	layMain->addLayout(layMapGrid);
	layMain->addLayout(layButton);
	layMain->addWidget(btnLeave);

	MainMenu->setLayout(layMain);

}

QWidget* QMapSelectionMenu::GetMenu()
{
	return MainMenu;
}

void QMapSelectionMenu::OnEnter()
{
	SelectMap(0);
}

void QMapSelectionMenu::OnLeave()
{
	SelectMap(0);
}

bool QMapSelectionMenu::OnMapSelect()
{
	std::vector<nlohmann::json> allMaps = GetAllMaps();
	amountOfMaps = (int)allMaps.size();

	// Corruption detection
	if (GetMapJsonError(allMaps[appRef->selection]) != EM_MAP_NO_ERROR)
	{
		return false;
	}

	map = new Map(allMaps[appRef->selection]);
	DrawSelectedMap();
	return true;
}

void QMapSelectionMenu::DrawSelectedMap() 
{

	int sizeX = map->GetSizeX();
	int sizeY = map->GetSizeY();
	lblMapName->setText(QString("Name: %1").arg(QString::fromStdString(map->GetName())));
	lblNbPlayer->setText(QString("Number of player: %1").arg(map->GetAmountOfPlayer()));
	lblMapSize->setText(QString("Size of the map: %1 by %2").arg(sizeX).arg(sizeY));

	for (int j = 0; j < sizeY; ++j) {
		QVector<QLabel*> temp;
		for (int i = 0; i < sizeX; ++i) {
			

			lblMapCell = new QLabel("X");
			lblMapCell->setText(QString::fromStdString(map->tileChar[map->GetTileDataAtPosition(i, j)]));
			layMapGrid->addWidget(lblMapCell, i, j);
			temp.append(lblMapCell);
		}
		gridContent.append(temp);
	}
}

void QMapSelectionMenu::ClearMapGrid() 
{
	int sizeX = map->GetSizeX();
	int sizeY = map->GetSizeY();
	for (int j = 0; j < sizeY; ++j) 
	{
		for (int i = 0; i < sizeX; ++i) 
		{
			layMapGrid->removeWidget(gridContent[i][j]);
		}
	}
	gridContent.clear();
}

void QMapSelectionMenu::Play() 
{
	appRef->wantedMapIndex = appRef->selection;
	appRef->SetNewQMenu(QMenus::PlayerJoining);
}

void QMapSelectionMenu::SelectMap(int selected) 
{
	appRef->selection = selected;
	OnMapSelect();
}

void QMapSelectionMenu::SelectionNext() 
{
	ClearMapGrid();
	appRef->selection++;
	if (appRef->selection > amountOfMaps - 1) appRef->selection = 0;
	OnMapSelect();
}

void QMapSelectionMenu::SelectionPrevious() 
{
	ClearMapGrid();
	appRef->selection--;
	if (appRef->selection < 0) appRef->selection = amountOfMaps - 1;
	if (appRef->selection < 0) appRef->selection = 0;
	OnMapSelect();
}

void QMapSelectionMenu::GoBack()
{
	appRef->SetNewQMenu(QMenus::MainMenu);
}