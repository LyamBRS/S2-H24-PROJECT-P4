/**
 * @file QPlayerJoiningMenu.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-04-05
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "QPlayerJoiningMenu.h"

// - CLASS - //
QPlayerJoiningMenu::QPlayerJoiningMenu()
{

}


QPlayerJoiningMenu::QPlayerJoiningMenu(QMainWindow* windowReference, AppHandler* appHandler)
{
	winRef = windowReference;
	appRef = appHandler;

	CreateGame();
	CreateTimers();
	CreateWidgets();
	CreateLayouts();
	ConnectWidgets();
	CreateMenu();
}

void QPlayerJoiningMenu::CreateTimers()
{

}


void QPlayerJoiningMenu::CreateWidgets()
{
	WaitingForPlayersToJoinLabel = new QLabel("Waiting for players to join");

	JoinedPlayersProgress = new QProgressBar();
	JoinedPlayersProgress->setRange(0, appRef->currentGame->GetMaxPlayerCount());

	JoinedPlayersList = new QJoinedPlayersList(appRef->currentGame->GetMaxPlayerCount());

	CancelButton = new QPushButton("Cancel");
	StartGameButton = new QPushButton("Start");

	MainMenu = new QWidget();
}

void QPlayerJoiningMenu::CreateLayouts()
{
	MainLayout = new QGridLayout();
}

void QPlayerJoiningMenu::ConnectWidgets()
{
	connect(CancelButton,	 &QPushButton::clicked, this, &QPlayerJoiningMenu::CancelPressed);
	connect(StartGameButton, &QPushButton::clicked, this, &QPlayerJoiningMenu::StartGamePressed);

	connect(appRef->currentGame, &BomberManGame::AmountOfConnectedPlayersChanged, this, &QPlayerJoiningMenu::PlayerCountChanged);
	connect(appRef->currentGame, &BomberManGame::PlayerConnected, this, &QPlayerJoiningMenu::PlayerConnected);
	connect(appRef->currentGame, &BomberManGame::PlayerDisconnected, this, &QPlayerJoiningMenu::PlayerDisconnected);
}

void QPlayerJoiningMenu::CreateMenu()
{
	MainLayout->addWidget(WaitingForPlayersToJoinLabel, 0, 0, 1, 2);
	MainLayout->addWidget(JoinedPlayersProgress,		1, 0, 1, 2);
	MainLayout->addWidget(JoinedPlayersList,			2, 0, 10, 2);
	MainLayout->addWidget(CancelButton,		13, 0, 1, 1);
	MainLayout->addWidget(StartGameButton,	13, 1, 1, 1);

	MainMenu->setLayout(MainLayout);
}

void QPlayerJoiningMenu::CreateGame()
{
	// Get all available maps
	std::vector<nlohmann::json> allMaps = GetAllMaps();
	int amountOfMaps = (int)allMaps.size();

	// Validate the given JSON of the specified index.
	if (appRef->wantedMapIndex < 0 || appRef->wantedMapIndex >= amountOfMaps)
	{
		std::cout << "GAME wantedMapIndex ERROR" << std::endl;
		//return false;

		//TODO: Add error management here. Display game creation error.
		return;
	}

	if (GetMapJsonError(allMaps[appRef->wantedMapIndex]) != EM_MAP_NO_ERROR)
	{
		std::cout << "GAME GetMapJsonError ERROR" << std::endl;
		//TODO: Add error management here. Display game creation error.
		return;
	}

	Map* currentMap = new Map(allMaps[appRef->wantedMapIndex]);
	appRef->currentGame = new BomberManGame(appRef, currentMap);

	if (!appRef->currentGame->isValidated())
	{
		std::cout << "GAME isValidated ERROR" << std::endl;
		//TODO: Add error management here. Display game creation error.
		return;
	}

	// Reset all hardware controllers's IDs so that they are valid again to be assigned to players.
	for (int i = 1; i <= CONTROLLER_TYPE_AMOUNT; i++)
	{
		appRef->GetHardwareController(i)->controllerID = 0;
	}

	appRef->SetMessage(" Please join... ");
}



void QPlayerJoiningMenu::CancelPressed()
{
	appRef->SetNewQMenu(QMenus::MainMenu);
}

void QPlayerJoiningMenu::StartGamePressed()
{
	appRef->currentGame->Start();
	appRef->SetNewQMenu(QMenus::Game);
}

void QPlayerJoiningMenu::PlayerCountChanged(int newPlayerCount)
{
	if (newPlayerCount != appRef->currentGame->GetConnectedPlayerCount())
	{
		qFatal() << " newPlayerCount does not match GetConnectedPlayerCount";
	}

	JoinedPlayersProgress->setValue(newPlayerCount);
}

void QPlayerJoiningMenu::PlayerConnected(int playerID, int realWorldControllerID)
{
	QColor associatedColour;
	switch (playerID)
	{
		case(0): associatedColour = *appRef->colorPlayerA; break;
		case(1): associatedColour = *appRef->colorPlayerB; break;
		case(2): associatedColour = *appRef->colorPlayerC; break;
		case(3): associatedColour = *appRef->colorPlayerD; break;
		case(4): associatedColour = *appRef->colorPlayerE; break;
	}

	JoinedPlayersList->SetSlot(playerID, true, realWorldControllerID, associatedColour);
}

void QPlayerJoiningMenu::PlayerDisconnected(int playerID)
{
	QColor associatedColour;
	switch (playerID)
	{
		case(0): associatedColour = *appRef->colorPlayerA; break;
		case(1): associatedColour = *appRef->colorPlayerB; break;
		case(2): associatedColour = *appRef->colorPlayerC; break;
		case(3): associatedColour = *appRef->colorPlayerD; break;
		case(4): associatedColour = *appRef->colorPlayerE; break;
	}

	JoinedPlayersList->SetSlot(playerID, false, 0, associatedColour);
}












QWidget* QPlayerJoiningMenu::GetMenu()
{
	return MainMenu;
}

void QPlayerJoiningMenu::OnEnter()
{
	for (int i = 1; i <= CONTROLLER_TYPE_AMOUNT; i++)
	{
		appRef->GetHardwareController(i)->controllerID = 0;
	}

	switch (appRef->currentGame->GetStatus())
	{
	case(GameStatuses::awaitingConnection):
		break;

	case(GameStatuses::awaitingPlayers):
		// We're good!
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
		appRef->SetNewQMenu(QMenus::PlayingGame);
		break;
	}
}

void QPlayerJoiningMenu::OnLeave()
{

}