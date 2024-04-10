/**
 * @file QMapSelectionMenu.h
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
#include <QApplication>
#include <QTimer>
#include <qmenubar.h>
#include "../Application/AppHandler.h"
#include "../Map/Utils.hpp"
#include "../Map/Map.h"
#include "../JSON/json.hpp"

// - DEFINES - //

// - CLASS - //

class QMapSelectionMenu : public QObject
{

public:
	QMapSelectionMenu();
	QMapSelectionMenu(QMainWindow* windowReference, AppHandler* appHandler);

	QWidget* GetMenu();

	void OnEnter();
	void OnLeave();
	
	Map* map;

	
	bool Draw();// ned to def

public slots:
	void GoToSettings();
	void GoBack();
	void SelectionNext();
	void SelectionPrevious();
	void Play();

private:
	void DrawSelectedMap();
	void ClearMapGrid();
	void SelectMap(int selected);
	bool OnMapSelect();

	QMainWindow* winRef;
	AppHandler* appRef;

	QPushButton* btnPlay;
	QPushButton* btnSelectionRight;
	QPushButton* btnSelectionLeft;
	QPushButton* btnLeave;

	QLabel* lblNbPlayer;
	QLabel* lblMapName;
	QLabel* lblMapSize;

	QGridLayout* layMapGrid;
	QVBoxLayout* layMain;
	QHBoxLayout* layButton;
	QHBoxLayout* layLabels;

	QWidget* MainMenu;
	QVector<QVector<QLabel*>> gridContent;


	int amountOfMaps = 0;

};