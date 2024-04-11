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
#include "../Serial/PortDetector.h"
#include <QWidget>
#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <qmenubar.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qprogressdialog.h>
#include <qmessagebox.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qstyleditemdelegate.h>
#include <qpainter.h>
#include <qtimer.h>
#include <qprogressbar.h>
#include <qgridlayout.h>
#include "../Application/AppHandler.h"

// - DEFINES - //

// - FUNCTIONS - //
QStringList GetComPorts();
QStringList GetBaudRates();

// - CLASS - //

class CustomComboBox : public QComboBox
{
public:
	CustomComboBox(QWidget* parent = nullptr) : QComboBox(parent) {}

protected:
	void paintEvent(QPaintEvent* event) override
	{
		QComboBox::paintEvent(event);

		// Get the text of the selected item
		QString selectedText = currentText();

		// If the selected item is not in the list, paint it in red
		if (!itemText(currentIndex()).isEmpty() && itemText(currentIndex()) != selectedText)
		{
			QPainter painter(this);
			painter.setPen(Qt::red);
			painter.drawText(rect(), Qt::AlignCenter, selectedText);
		}
	}
};


class QSettingsMenu : public QObject
{
private:

	QMainWindow* winRef;
	AppHandler* appRef;

	QPushButton* backButton;
	QPushButton* connectButton;

	QComboBox* baudratesBox;
	CustomComboBox* comPortBox;

	QLabel* portStatus;
	QLabel* helperText;
	QLabel* rawReceivedMessageText;
	QLabel* baudRateText;
	QLabel* comPortText;

	//QProgressDialog* connectingDialog;
	//QMessageBox* helperDialog;

	QVBoxLayout* comboxBoxLayout;
	QVBoxLayout* buttonLayout;
	QVBoxLayout* leftLayout;
	QVBoxLayout* rawReceivedMessageLayout;
	QGridLayout* mainLayout;

	QHBoxLayout* baudrateLayout;
	QHBoxLayout* comPortLayout;

	QProgressBar* connectionProgress;

	QWidget* MainMenu;

	QTimer* amountOfComPortChecks;
	QTimer* connectingProgress;

	QWidget* leftArea;
	QWidget* rightArea;

public:
	QSettingsMenu();
	QSettingsMenu(QMainWindow* windowReference, AppHandler* appHandler);

	QWidget* GetMenu();

	void OnEnter();
	void OnLeave();

	int GetCurrentBaudRateIndex();
	int ComPortIndex();

	void CreateTimers();
	void CreateWidgets();
	void CreateLayouts();
	void ConnectWidgets();
	void CreateMenu();

public slots:
	void GoToMainMenu();
	void ConnectClicked();
	void BaudRateChanged(int index);
	void SelectedComPortChanged(int index);

	void ComPortChanged();
	void CheckOnConnectionStatus();
};