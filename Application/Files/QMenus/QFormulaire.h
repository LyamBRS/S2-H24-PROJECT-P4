/**
 * @file QSettingsMenu.h
 * @author LyamBRS
 * @brief
 * @version 0.1
 * @date 2024-04-08
 * @copyright Copyright (c) 2024
 */

#pragma once

 // - INCLUDES - //
#include <QWidget>
#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>
#include <qmenubar.h>

// - DEFINES - //

// - CLASS - //

class QFormulaire
{
private:

	QMainWindow* winRef;

	QPushButton* playButton;
	QPushButton* settingsButton;
	QPushButton* appButton;
	QPushButton* leaveButton;

	QVBoxLayout* MainLayout;
	QVBoxLayout* ButtonLayout;

	QWidget* MainMenu;

public:
	QFormulaire(QMainWindow* windowReference);

	QMainWindow* GetWindow();

	void OnEnter();
	void OnLeave();
};