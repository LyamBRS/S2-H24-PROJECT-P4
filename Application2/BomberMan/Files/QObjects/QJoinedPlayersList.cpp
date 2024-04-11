/**
 * @file QJoinedPlayersList.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-04-09
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "QJoinedPlayersList.h"


QJoinedPlayersSlot::QJoinedPlayersSlot(int slotID)
{
	playerID = slotID;

	MainWidget = new QWidget();
	MainLayout = new QHBoxLayout();
	MainLayout->setSpacing(0);

	TypeOfController = new QLabel("Disconnected");
	PlayerIcon = new QLabel("-");

	QString result = "Player ";
	if ((slotID + 1) < 10) result.append("0");
	result.append(std::to_string((slotID + 1)));
	PlayerID = new QLabel(result);

	TypeOfController->setEnabled(false);
	PlayerIcon->setEnabled(false);
	PlayerID->setEnabled(false);

	TypeOfController->setAlignment(Qt::AlignCenter);
	PlayerIcon->setAlignment(Qt::AlignCenter);
	PlayerID->setAlignment(Qt::AlignCenter);

	TypeOfController->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	PlayerIcon->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	PlayerID->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	MainLayout->addWidget(PlayerID);
	MainLayout->addWidget(TypeOfController);
	MainLayout->addWidget(PlayerIcon);

	setLayout(MainLayout);
}

QWidget* QJoinedPlayersSlot::GetWidget()
{
	return MainWidget;
}

void QJoinedPlayersSlot::Set(bool used, int realWorldControllerID, QColor associatedColour)
{
	if (used)
	{
		TypeOfController->setEnabled(true);
		PlayerIcon->setEnabled(true);
		PlayerID->setEnabled(true);

		TypeOfController->setText("Disconnected");

		QString slotValue = "ERROR";
		switch (realWorldControllerID)
		{
			case(1):
				slotValue = "Controller A";
				break;

			case(2):
				slotValue = "Controller B";
				break;

			case(3):
				slotValue = " L keyboard ";
				break;

			case(4):
				slotValue = " R keyboard ";
				break;

			case(5):
				slotValue = "BRS  GamePad";
				break;
		}

		PlayerIcon->setText("@");
		TypeOfController->setText(slotValue);

		QString styleSheet = QString("color: %1;").arg(associatedColour.name());
		TypeOfController->setStyleSheet(styleSheet);
		PlayerID->setStyleSheet(styleSheet);
		return;
	}

	TypeOfController->setEnabled(false);
	PlayerIcon->setEnabled(false);
	PlayerID->setEnabled(false);

	TypeOfController->setText("Disconnected");
	PlayerIcon->setText("-");


	QColor baseColor = QColor(QPalette::Text);
	QString styleSheet = QString("color: %1;").arg(baseColor.name());
	TypeOfController->setStyleSheet(styleSheet);
	PlayerID->setStyleSheet(styleSheet);
}












QJoinedPlayersList::QJoinedPlayersList(int amountOfSlots)
{
	QPalette palette = this->palette();
	palette.setColor(QPalette::Window, palette.color(QPalette::AlternateBase));  // Using AlternateBase color
	this->setPalette(palette);
	this->setAutoFillBackground(true);

	QColor secondaryColor = palette.color(QPalette::Dark);
	QString styleSheet = QString("background-color: %1;").arg(secondaryColor.name());
	this->setStyleSheet(styleSheet);

	MainWidget = new QWidget();
	MainLayout = new QVBoxLayout();

	for (int i = 0; i < amountOfSlots; i++)
	{
		QJoinedPlayersSlot* newSlot = new QJoinedPlayersSlot(i);
		playerSlots.append(newSlot);
		MainLayout->addWidget(newSlot);
	}

	MainLayout->setSpacing(0);
	setLayout(MainLayout);
	//MainWidget->setLayout(MainLayout);
}

QWidget* QJoinedPlayersList::GetWidget()
{
	return MainWidget;
}


void QJoinedPlayersList::EventUpdateSlot(int slotIndex, int realWorldControllerID)
{

}

void QJoinedPlayersList::SetSlot(int slotIndex, bool used, int controllerType, QColor associatedColour)
{
	playerSlots[slotIndex]->Set(used, controllerType, associatedColour);
}
