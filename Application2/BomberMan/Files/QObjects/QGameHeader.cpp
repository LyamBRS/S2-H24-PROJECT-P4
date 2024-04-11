/**
 * @file QGameHeader.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-04-10
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "QGameHeader.h"

QGameHeader::QGameHeader()
{
	CreateWidgets();
	CreateLayouts();
	ConnectWidgets();
	BuildWidget();

	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	QPalette palette = this->palette();
	QColor backgroundColour = palette.color(QPalette::Mid);

	QString styleSheet = QString("background-color: %1;")
		.arg(backgroundColour.name());

	setAutoFillBackground(true);
	this->setStyleSheet(styleSheet);
}

/// @brief true: chrono, false: countdown
void QGameHeader::SetChronoMode(bool newMode)
{
	inChronoMode = newMode;
}

void QGameHeader::SetCountdownValue(int value)
{
	if (inChronoMode) return;
	switch (value)
	{
	case(0):
		ChronoLabel->setText("GO");
		break;

	case(1):
		ChronoLabel->setText("GO");
		break;

	case(2):
		ChronoLabel->setText("1");
		break;

	case(3):
		ChronoLabel->setText("2");
		break;

	case(4):
		ChronoLabel->setText("3");
		break;
	}
}

void QGameHeader::SetChronoValue(uint64_t newValue) 
{
	if (!inChronoMode) return;
	int seconds = chronoRef->GetClockSeconds();
	int minutes = chronoRef->GetClockMinutes();
	int hours = chronoRef->GetClockHours();

	QString qSeconds = QString::number(seconds);
	QString qMinutes = QString::number(minutes);
	QString qHours = QString::number(hours);

	if (qSeconds.length() == 1) qSeconds.insert(0, "0");
	if (qMinutes.length() == 1) qMinutes.insert(0, "0");
	if (qHours.length() == 1) qHours.insert(0, "0");

	QString result = qHours;
	result += ":";
	result += qMinutes;
	result += ":";
	result += qSeconds;

	ChronoLabel->setText(result);
}

void QGameHeader::BindChrono(SimpleChrono* chrono)
{
	chronoRef = chrono;
}

void QGameHeader::SetMapName(QString name)
{
	MapNameLabel->setText(name);
}

void QGameHeader::SetTotalPlayerCount(int newTotal)
{
	PlayerLeftProgressBar->setRange(0, newTotal);
	PlayerLeftProgressBar->setValue(newTotal);
}

void QGameHeader::SetAsPaused()
{
	inChronoMode = true;
	PauseResumeButton->setEnabled(true);
	PauseResumeButton->setText(PAUSED_TEXT);
}

void QGameHeader::SetAsEnded()
{
	inChronoMode = true;
	PauseResumeButton->setEnabled(false);
	PauseResumeButton->setText("Ended");
	PlayerLeftProgressBar->setValue(0);
}

void QGameHeader::SetAsPlaying()
{
	inChronoMode = true;
	PauseResumeButton->setEnabled(true);
	PauseResumeButton->setText(PLAYING_TEXT);
}

void QGameHeader::SetAsCountDown()
{
	inChronoMode = false;
	PauseResumeButton->setEnabled(false);
	PauseResumeButton->setText("Wait...");

	ChronoLabel->setText("");
	PlayerLeftProgressBar->setValue(maxPlayerCount);
}

// - SLOTS - //
void QGameHeader::PausePressed()
{
	emit PauseButtonPressed();
}

void QGameHeader::PlayerLeftChanged(int newPlayerCount)
{
	PlayerLeftProgressBar->setValue(newPlayerCount);
}

void QGameHeader::ChronoChanged(uint64_t newValue)
{
	SetChronoValue(newValue);
}

void QGameHeader::UpdateFromGameStatus(int gameStatus)
{
	switch (gameStatus)
	{
		case(GameStatuses::countdown):	SetAsCountDown();	return;
		case(GameStatuses::playing):	SetAsPlaying();		return;
		case(GameStatuses::paused):		SetAsPaused();		return;
		case(GameStatuses::ended):		SetAsEnded();		return;
	}
}

void QGameHeader::CountDownChanged(int newCount)
{
	SetCountdownValue(newCount);
}

void QGameHeader::CreateWidgets()
{
	QPalette palette = this->palette();
	QColor backgroundColour = palette.color(QPalette::Mid);
	QColor BorderColour = palette.color(QPalette::Shadow);
	QColor ChronoBackground = palette.color(QPalette::Dark);

	QString styleSheet = QString("background-color: %1;").arg(backgroundColour.name());

	QString chronoStyleSheet = QString("background-color: %1; border: 2px solid %2;")
		.arg(ChronoBackground.name())
		.arg(BorderColour.name());

	PlayerLeftProgressBar	= new QProgressBar();
	PauseResumeButton		= new QPushButton(PLAYING_TEXT);
	MapNameLabel			= new QLabel("None");
	ChronoLabel				= new QLabel("0");

	MapNameLabel->setAlignment(Qt::AlignCenter);

	PlayerLeftProgressBar->setFormat("");
	PlayerLeftProgressBar->setAutoFillBackground(true);
	PlayerLeftProgressBar->setStyleSheet(styleSheet);

	ChronoLabel->setAlignment(Qt::AlignCenter);
	QFont font = ChronoLabel->font();
	font.setPointSize(font.pointSize() * 2);
	ChronoLabel->setFont(font);
	ChronoLabel->setStyleSheet(chronoStyleSheet);



	ChronoLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	ChronoLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	MapNameLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	PauseResumeButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void QGameHeader::CreateLayouts()
{
	MainLayout = new QGridLayout();
	MainLayout->setSpacing(0);
}

void QGameHeader::ConnectWidgets()
{
	connect(PauseResumeButton, &QPushButton::clicked, this, &QGameHeader::PauseButtonPressed);
}

void QGameHeader::BuildWidget()
{
	MainLayout->addWidget(ChronoLabel,				0, 0, 2, 3);
	MainLayout->addWidget(MapNameLabel,				0, 3, 1, 7);
	MainLayout->addWidget(PauseResumeButton,		1, 3, 1, 2);
	MainLayout->addWidget(PlayerLeftProgressBar,	1, 5, 1, 6);
	setLayout(MainLayout);
}