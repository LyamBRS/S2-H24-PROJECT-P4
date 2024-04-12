/**
 * @file QPlayerStats.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-04-10
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "QPlayerStats.h"


QPlayerStat::QPlayerStat(int playerID, QColor associatedColor)
{
	MainLayout = new QVBoxLayout();
	TopLayout = new QHBoxLayout();

	PlayerNameLabel = new QLabel();
	HealthProgressBar = new QProgressBar();
	HealthProgressBar->setRange(0, 100);
	HealthProgressBar->setValue(100);

	InventoryLayout = new QHBoxLayout();

	QPixmap pm(QString::fromStdString(GetSvg(TileTypes::EMPTY)));
	auto newPixmap = pm.scaled(INVENTORY_SVG_SCALE, INVENTORY_SVG_SCALE);
	for (int i = 0; i < INVENTORY_MAX_SLOT; i++)
	{
		QLabel* slot = new QLabel();
		slot->setPixmap(newPixmap);
		slot->setAlignment(Qt::AlignCenter);
		inventorySlots.append(slot);
		InventoryLayout->addWidget(slot);
	}

	// - PLAYER NAME - //
	QString result = "Player ";
	if ((playerID + 1) < 10) result.append("0");
	result.append(std::to_string((playerID + 1)));
	PlayerNameLabel->setText(result);

	QFont font = PlayerNameLabel->font();
	font.setPointSize(font.pointSize() * 2);
	PlayerNameLabel->setFont(font);

	QString styleSheet = QString("color: %1;").arg(associatedColor.name());
	PlayerNameLabel->setStyleSheet(styleSheet);

	// - CREATE WIDGET - //
	TopLayout->addWidget(PlayerNameLabel);
	TopLayout->addWidget(HealthProgressBar);
	MainLayout->addLayout(TopLayout);

	MainLayout->addLayout(InventoryLayout);
	setLayout(MainLayout);
}

void QPlayerStat::LinkPlayer(Player* player)
{
	playerRef = player;
}

void QPlayerStat::HealthChanged()
{
	HealthProgressBar->setValue(playerRef->Health());
}

void QPlayerStat::InventoryChanged()
{
	Inventory* inventory = playerRef->GetInventory();
	int currentSelectedIndex = inventory->CurrentIndex();
	
	QPalette palette = this->palette();
	QColor BorderColour = palette.color(QPalette::Shadow);


	for (int i = 0; i < INVENTORY_MAX_SLOT; i++)
	{
		PowerUp* powerUp = inventory->Get(i);

		QString styleSheet = "";
		if (i == currentSelectedIndex)
		{
			styleSheet = QString("border: 1px solid %1;")
				.arg(BorderColour.name());
		}
		else
		{
			styleSheet = QString("border: None;");
		}

		QLabel* slot = inventorySlots[i];
		slot->setStyleSheet(styleSheet);

		// Transform the current power up into a tile so I can get the appropriate SVG from it.
		TileTypes associatedTile = GetTileFromPowerUp(powerUp->getType());

		QPixmap pm(QString::fromStdString(GetSvg(associatedTile)));
		auto newPixmap = pm.scaled(INVENTORY_SVG_SCALE, INVENTORY_SVG_SCALE);
		slot->setPixmap(newPixmap);
	}
}












QPlayerStatsList::QPlayerStatsList(int playerCount, BomberManGame* currentGame, AppHandler* handler)
{
	playerCountRef = playerCount;

	mainLayout = new QVBoxLayout();
	mainLayout->setSpacing(0);

	for (int i = 0; i < playerCountRef; i++)
	{

		QColor associatedColour;
		switch (i)
		{
		case(0): associatedColour = *handler->colorPlayerA; break;
		case(1): associatedColour = *handler->colorPlayerB; break;
		case(2): associatedColour = *handler->colorPlayerC; break;
		case(3): associatedColour = *handler->colorPlayerD; break;
		case(4): associatedColour = *handler->colorPlayerE; break;
		}

		QPlayerStat* stats = new QPlayerStat(i, associatedColour);
		stats->LinkPlayer(currentGame->GetPlayer(i));
		playerSlots.append(stats);

		if (currentGame->GetPlayer(i)->GetController()->controllerID != 0)
		{
			mainLayout->addWidget(stats);
		}
	}

	setLayout(mainLayout);
}

void QPlayerStatsList::LinkPlayer(int playerID, Player* player)
{
	playerSlots[playerID]->LinkPlayer(player);
}

void QPlayerStatsList::HealthEvent()
{
	for (int i = 0; i < playerCountRef; i++)
	{
		playerSlots[i]->HealthChanged();
	}
}

void QPlayerStatsList::InventoryEvent()
{
	for (int i = 0; i < playerCountRef; i++)
	{
		playerSlots[i]->InventoryChanged();
	}
}