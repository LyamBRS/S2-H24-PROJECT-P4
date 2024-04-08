/**
 * @file QMainMenu.h
 * @author LyamBRS
 * @brief
 * @version 0.1
 * @date 2024-04-05
 * @copyright Copyright (c) 2024
 */

#pragma once

 // - INCLUDES - //
#include <QtWidgets>
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

class QMainMenu : public QObject
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

private slots:
	void GoToSettings();

public:
	QMainMenu(QMainWindow* windowReference);

	QMainWindow* GetWindow();

	void OnEnter();
	void OnLeave();
};