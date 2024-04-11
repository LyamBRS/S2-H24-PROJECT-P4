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
	appRef = appHandler;
	winRef = windowReference;

	CreateTimers();
	CreateWidgets();
	CreateLayouts();
	ConnectWidgets();
	PutWidgetsInMenu();

	if (appRef->currentGame->GetConnectedPlayerCount() == 0)
	{
		qFatal() << "No players were connected";
	}

	//appRef->currentSelectedMenu = APP_GAME_MENU;
}

void QGameMenu::CreateTimers()
{

}

void QGameMenu::CreateWidgets()
{
	GameHeader = new QGameHeader();
	GameHeader->SetAsCountDown();
	GameHeader->BindChrono(&appRef->currentGame->gameDuration);
	GameHeader->SetMapName(QString::fromStdString(appRef->currentGame->GetMap()->GetName()));
	GameHeader->SetTotalPlayerCount(appRef->currentGame->GetActualPlayerCount());

	GameMap = new QBomberManMap();
	GameMap->SetMapReference(appRef->currentGame->GetMap());
	GameMap->SetTileColor(TileTypes::PLAYER1, *appRef->colorPlayerA);
	GameMap->SetTileColor(TileTypes::PLAYER2, *appRef->colorPlayerB);
	GameMap->SetTileColor(TileTypes::PLAYER3, *appRef->colorPlayerC);
	GameMap->SetTileColor(TileTypes::PLAYER4, *appRef->colorPlayerD);
	//GameMap->SetTileColor(TileTypes::PLAYER5, *appRef->colorPlayerE);

	PlayersStats = new QPlayerStatsList(appRef->currentGame->GetMaxPlayerCount(), appRef->currentGame);

	MainMenu = new QWidget();
	GameMap->SetAsPaused();
}

void QGameMenu::CreateLayouts()
{
	MainLayout	= new QVBoxLayout();
	TopLayout	= new QVBoxLayout();
	BottomLayout = new QHBoxLayout();
}

void QGameMenu::ConnectWidgets()
{
	connect(GameHeader->PauseResumeButton, &QPushButton::clicked, this, &QGameMenu::PauseResumeButtonPressed);

	connect(appRef->currentGame, &BomberManGame::CountDownChanged, GameHeader, &QGameHeader::CountDownChanged);
	connect(appRef->currentGame, &BomberManGame::PlayerDeath, GameHeader, &QGameHeader::PlayerLeftChanged);
	connect(appRef->currentGame, &BomberManGame::StatusChanged, GameHeader, &QGameHeader::UpdateFromGameStatus);
	connect(appRef->currentGame, &BomberManGame::GameTimerChanged, GameHeader, &QGameHeader::ChronoChanged);

	connect(appRef->currentGame->GetMap(), &Map::TileDataChanged, GameMap, &QBomberManMap::TileChanged);

	connect(appRef->currentGame, &BomberManGame::HealthChanged, PlayersStats, &QPlayerStatsList::HealthEvent);
	connect(appRef->currentGame, &BomberManGame::InventoryChanged, PlayersStats, &QPlayerStatsList::InventoryEvent);

	connect(appRef->currentGame, &BomberManGame::StatusChanged, this, &QGameMenu::GameStatusChanged);
}

void QGameMenu::PutWidgetsInMenu()
{
	TopLayout->addWidget(GameHeader);
	BottomLayout->addWidget(GameMap);
	BottomLayout->addWidget(PlayersStats);

	MainLayout->addLayout(TopLayout);
	MainLayout->addLayout(BottomLayout);

	MainMenu->setLayout(MainLayout);
}

void QGameMenu::SetAsPaused()
{
	GameMap->SetAsPaused();

	QMessageBox msgBox;
	msgBox.setWindowTitle("Game is paused");
	msgBox.setText("The game is currently paused. Do you wish to resume?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes); // Set default button to Yes

	// Execute the dialog and handle the button clicked signal
	int choice = msgBox.exec();

	// Check which button was clicked
	if (choice == QMessageBox::Yes) {
		appRef->currentGame->Resume();
	}
	else if (choice == QMessageBox::No) {
		appRef->SetNewQMenu(QMenus::MainMenu);
	}
}

void QGameMenu::SetAsPlaying()
{
	GameMap->SetAsPlaying();
}

void QGameMenu::SetAsEnded()
{
	GameMap->SetAsPaused();

	// Get the name of the winning player
	int playerID = appRef->currentGame->GetWinningPlayerID();
	QString result = "The game has ended! The winning player is: Player ";
	if ((playerID + 1) < 10) result.append("0");
	result.append(std::to_string((playerID)));

	QMessageBox msgBox;
	msgBox.setWindowTitle("Game ended");
	msgBox.setText(result);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok); // Set default button to Yes

	msgBox.exec();

	appRef->SetNewQMenu(QMenus::MainMenu);
}

void QGameMenu::SetAsCountdown()
{

}

// - SLOTS - //
void QGameMenu::PauseResumeButtonPressed()
{
	if (appRef->currentGame->GetStatus() == GameStatuses::playing)
	{
		if (!appRef->currentGame->Pause())
		{
			qFatal() << "Failed to pause the game";
		}
	}
	else
	{
		if (!appRef->currentGame->Resume())
		{
			qFatal() << "Failed to resume the game";
		}
	}
}

void QGameMenu::MapTileChanged(int x, int y, TileTypes newTile)
{

}

void QGameMenu::GameTimerChanged(uint64_t newTime)
{

}

void QGameMenu::CountDownValueChanged(int newValue)
{

}

void QGameMenu::PlayerHealthChanged(int playerID, int newHealth)
{

}

void QGameMenu::PlayerDied(int playerID)
{

}

void QGameMenu::PlayerSelectedNewInventorySlot(int playerID, int slotNumber)
{

}

void QGameMenu::PlayerInventoryChanged(int playerID)
{

}

void QGameMenu::PlayerDisconnected(int playerID)
{

}

void QGameMenu::GameStatusChanged(int newStatus)
{
	switch (newStatus)
	{
		case(GameStatuses::playing):
			SetAsPlaying();
			break;

		case(GameStatuses::paused):
			SetAsPaused();
			break;

		case(GameStatuses::ended):
			SetAsEnded();
			break;
	}
}






QWidget* QGameMenu::GetMenu()
{
	return MainMenu;
}

void QGameMenu::OnEnter()
{

}

void QGameMenu::OnLeave()
{

}