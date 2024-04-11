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
#include <QTextEdit>
#include <QLabel>
#include <QDialog>
#include <QLayout>
#include <iostream>
#include <QStatusBar>
#include <QMenuBar>

#include "../Application/AppHandler.h"

// - DEFINES - //
// - CLASS - //

class QFormulaire : public QObject
{

private:

    QMainWindow* winRef;
    AppHandler* appRef;

    QMenuBar* menuBar;
    QMenu* choixMenu;
    QAction* actionPlay;
    QAction* actionSettings;
    QAction* actionLeave;

    QWidget* MainMenu;

    QPushButton* leaveButton;
	QPushButton* confirmer_joueur1;
	QPushButton* confirmer_joueur2;

	QVBoxLayout* MainLayout;
	QVBoxLayout* ButtonLayout;
    QVBoxLayout* LabelLayout1;
    QVBoxLayout* LabelLayout2;
    QVBoxLayout* MenuLayout;
    QVBoxLayout* NomJoueur1;
    QVBoxLayout* NomJoueur2;

	QTextEdit* joueur1;
	QTextEdit* joueur2;

	QLabel* label_joueur1;
	QLabel* label_joueur2;
	QLabel* titre_formulaire;

    static QString nom_du_joueur1;
    static QString nom_du_joueur2;

public:
    QFormulaire();
    QFormulaire(QMainWindow* windowReference, AppHandler* appHandler);

    QWidget* GetMenu();

    void OnEnter();
    void OnLeave();
    void SetPlayerNames();

public slots:
    void GoToMainMenu();
    void GoToPlayMenu();
    void GoToSettingsMenu();
    void GoToLeaveMenu();
    void popup_1();
    void popup_2();
};