/**
 * @file QGameHeader.h
 * @author LyamBRS
 * @brief
 * @version 0.1
 * @date 2024-04-10
 * @copyright Copyright (c) 2024
 */

#pragma once

 // - INCLUDES - //
#include <QtWidgets>
#include "../Game/Game.h"
#include "../SimpleTimer/SimpleChrono.h"

// - DEFINES - //
#define PAUSED_TEXT "Resume"
#define PLAYING_TEXT "Pause"

// - CLASS - //

class QGameHeader : public QWidget
{
	Q_OBJECT
	
public:
	QGameHeader();

	/// @brief true: chrono, false: countdown
	void SetChronoMode(bool newMode);
	void SetCountdownValue(int value);
	void SetChronoValue(uint64_t newValue);
	void SetMapName(QString name);
	void SetTotalPlayerCount(int newTotal);
	void BindChrono(SimpleChrono* chrono);

	void SetAsPaused();
	void SetAsEnded();
	void SetAsPlaying();
	void SetAsCountDown();

	QPushButton* PauseResumeButton;

public slots:
	void PlayerLeftChanged(int newPlayerCount);
	void ChronoChanged(uint64_t newValue);
	void UpdateFromGameStatus(int gameStatus);
	void CountDownChanged(int newCount);

private slots:
	void PausePressed();

signals:
	void PauseButtonPressed();

private:

	bool inChronoMode = false;
	int maxPlayerCount = 0;

	void CreateWidgets();
	void CreateLayouts();
	void ConnectWidgets();
	void BuildWidget();

	QGridLayout* MainLayout;
	QProgressBar* PlayerLeftProgressBar;
	QLabel* MapNameLabel;
	QLabel* ChronoLabel;

	SimpleChrono* chronoRef;
};