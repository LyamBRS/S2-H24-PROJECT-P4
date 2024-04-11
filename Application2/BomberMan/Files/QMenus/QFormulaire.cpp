/**
 * @file QSettingsMenu.cpp
 * @author LyamBRS
 * @brief
 * @version 0.1
 * @date 2024-04-08
 * @copyright Copyright (c) 2024
 */

 // - INCLUDES - //
#include "QFormulaire.h"

// - CLASS - //
QFormulaire::QFormulaire()
{

}

QFormulaire::QFormulaire(QMainWindow* windowReference, AppHandler* appHandler)
{
	winRef = windowReference;
	appRef = appHandler;

	MainMenu = new QWidget();

	//Ajouter le titre du menu
	titre_formulaire = new QLabel("Menu Formulaire");

	// Ajouter la barre de menu � votre layout principal
	menuBar = new QMenuBar(winRef);
	choixMenu = new QMenu("Choix de menu", winRef);
	menuBar->addMenu(choixMenu);

	// Ajouter des actions au menu
	actionPlay = choixMenu->addAction("Menu Play");
	actionSettings = choixMenu->addAction("Menu Settings");
	actionLeave = choixMenu->addAction("Menu Leave");
	// Connecter les actions
	connect(actionPlay, &QAction::triggered, this, &QFormulaire::GoToPlayMenu);
	connect(actionSettings, &QAction::triggered, this, &QFormulaire::GoToSettingsMenu);
	connect(actionLeave, &QAction::triggered, this, &QFormulaire::GoToLeaveMenu);

	//Ajouter les labels et les zones de textes
	label_joueur1 = new QLabel("Quel est le nom du joueur 1?");
	joueur1 = new QTextEdit(nom_du_joueur1);
	joueur1->setFixedSize(200, 25);

	label_joueur2 = new QLabel("Quel est le nom du joueur 2?");
	joueur2 = new QTextEdit(nom_du_joueur2);
	joueur2->setFixedSize(200, 25);

	// Ajouter les boutons � votre layout principal
	leaveButton = new QPushButton("Back");
	// Connecter les signaux des boutons
	connect(leaveButton, &QPushButton::clicked, this, &QFormulaire::GoToMainMenu);

	//Ajouter les boutons pour faire apparaitre les dialogues de confirmation
	confirmer_joueur1 = new QPushButton("Confirmer");
	confirmer_joueur2 = new QPushButton("Confirmer");
	//Connecter les signaux des boutons
	connect(confirmer_joueur1, &QPushButton::clicked, this, &QFormulaire::popup_1);
	connect(confirmer_joueur2, &QPushButton::clicked, this, &QFormulaire::popup_2);


	// Faire un layout
	MainLayout = new QVBoxLayout();
	ButtonLayout = new QVBoxLayout();
	MenuLayout = new QVBoxLayout();
	LabelLayout1 = new QVBoxLayout();
	LabelLayout2 = new QVBoxLayout();
	NomJoueur1 = new QVBoxLayout();
	NomJoueur2 = new QVBoxLayout();

	// Placer les �l�ments dans le layout

	MenuLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	MenuLayout->addWidget(menuBar);
	MenuLayout->addWidget(titre_formulaire);

	ButtonLayout->setAlignment(Qt::AlignBottom | Qt::AlignRight);
	ButtonLayout->addWidget(leaveButton);

	LabelLayout1->setAlignment(Qt::AlignLeft);
	LabelLayout1->addWidget(label_joueur1);

	LabelLayout2->setAlignment(Qt::AlignLeft);
	LabelLayout2->addWidget(label_joueur2);

	NomJoueur1->setAlignment(Qt::AlignLeft);
	NomJoueur1->addWidget(joueur1);
	NomJoueur1->addWidget(confirmer_joueur1);

	NomJoueur2->setAlignment(Qt::AlignLeft);
	NomJoueur2->addWidget(joueur2);
	NomJoueur2->addWidget(confirmer_joueur2);


	//Afficher le Layout
	MainLayout->addLayout(MenuLayout);
	MainLayout->addLayout(LabelLayout1);
	MainLayout->addLayout(NomJoueur1);
	MainLayout->addLayout(LabelLayout2);
	MainLayout->addLayout(NomJoueur2);
	MainLayout->addLayout(ButtonLayout);
	MainMenu->setLayout(MainLayout);

}

QWidget* QFormulaire::GetMenu()
{
	return MainMenu;
}

void QFormulaire::OnEnter()
{

}

void QFormulaire::OnLeave()
{

}


void QFormulaire::popup_1() {
	QString playerName = joueur1->toPlainText();
	if (!playerName.isEmpty()) {
		nom_du_joueur1 = playerName; // Modifie la variable statique
		QMessageBox::information(winRef, "Nom du Joueur 1", "Le nom du joueur 1 est : " + playerName);
	}
	else {
		QMessageBox::warning(winRef, "Attention", "Veuillez entrer un nom pour le joueur 1.");
	}
}

void QFormulaire::popup_2() {
	QString playerName = joueur2->toPlainText();
	if (!playerName.isEmpty()) {
		nom_du_joueur2 = playerName; // Modifie la variable statique
		QMessageBox::information(winRef, "Nom du Joueur 2", "Le nom du joueur 2 est : " + playerName);
	}
	else {
		QMessageBox::warning(winRef, "Attention", "Veuillez entrer un nom pour le joueur 2.");
	}
}


void QFormulaire::GoToMainMenu()
{
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(winRef, "Confirmation", "Voulez vous vraiment quitter le formulaire ?",
		QMessageBox::Yes | QMessageBox::No);
	if (reply == QMessageBox::Yes) {
		SetPlayerNames();
		appRef->SetNewQMenu(QMenus::MainMenu);
	}
}

void QFormulaire::GoToPlayMenu()
{
	appRef->SetNewQMenu(QMenus::MainMenu);
}

void QFormulaire::GoToSettingsMenu()
{
	appRef->SetNewQMenu(QMenus::MainMenu);
}

void QFormulaire::GoToLeaveMenu()
{
	appRef->SetNewQMenu(QMenus::MainMenu);
}

void QFormulaire::SetPlayerNames() {
	joueur1->setText(nom_du_joueur1);
	joueur2->setText(nom_du_joueur2);
}

QString QFormulaire::nom_du_joueur1 = "";
QString QFormulaire::nom_du_joueur2 = "";