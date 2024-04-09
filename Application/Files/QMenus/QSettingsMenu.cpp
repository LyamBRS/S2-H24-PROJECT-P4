/**
 * @file QSettingsMenu.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-04-08
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "QSettingsMenu.h"






// - CLASS - //
QSettingsMenu::QSettingsMenu()
{

}

QSettingsMenu::QSettingsMenu(QMainWindow* windowReference, AppHandler* appHandler)
{
	winRef = windowReference;
	appRef = appHandler;

	amountOfComPortChecks = new QTimer();
	amountOfComPortChecks->setInterval(500);

	MainMenu = new QWidget();

	backButton		= new QPushButton("Back");
	connectButton = new QPushButton("Connect");

	baudratesBox = new QComboBox();
	comPortBox = new CustomComboBox();

	baudRateText = new QLabel("Baudrate:");
	comPortText  = new QLabel("Port:");
	helperText = new QLabel("helperText");
	portStatus = new QLabel("Port status");
	rawReceivedMessageText = new QLabel("ARDUINO MESSAGE IS SEEN HERE");

	buttonLayout = new QVBoxLayout();
	comboxBoxLayout = new QVBoxLayout();

	baudrateLayout = new QHBoxLayout();
	comPortLayout = new QHBoxLayout();

	rawReceivedMessageLayout = new QVBoxLayout();
	mainLayout = new QHBoxLayout();
	leftLayout = new QVBoxLayout();

	// - LABEL SETUPS - //
	helperText->setAlignment(Qt::AlignJustify);
	portStatus->setAlignment(Qt::AlignJustify);
	rawReceivedMessageText->setStyleSheet("border: 1px solid black;");

	// - LAYOUT SETUPS - //

	// - COMBO BOX SETUPS - //
	baudratesBox->addItems(GetBaudRates());
	baudratesBox->setCurrentIndex(GetCurrentBaudRateIndex());

	int selectedPort = ComPortIndex();
	comPortBox->addItems(GetComPorts());

	if (selectedPort == -1)
	{
		std::string stdResult = appRef->arduinoThread.GetArduino()->GetComPort();
		QString result = QString::fromStdString(stdResult);
		comPortBox->setCurrentText(result);
	}
	else
	{
		comPortBox->setCurrentIndex(selectedPort);
	}


	// - SIGNALS & SLOTS - CONNECTION - //
	connect(backButton, &QPushButton::clicked, this, &QSettingsMenu::GoToMainMenu);
	connect(connectButton, &QPushButton::clicked, this, &QSettingsMenu::ConnectClicked);
	connect(baudratesBox, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &QSettingsMenu::BaudRateChanged);
	connect(comPortBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &QSettingsMenu::SelectedComPortChanged);

	connect(amountOfComPortChecks, &QTimer::timeout, this, &QSettingsMenu::ComPortChanged);

	// - LAYOUT MAKING AND WIDGET ARRANGEMENTS - //
	buttonLayout->addWidget(connectButton);
	buttonLayout->addWidget(backButton);

	rawReceivedMessageLayout->addWidget(rawReceivedMessageText);

	baudrateLayout->addWidget(baudRateText);
	baudrateLayout->addWidget(baudratesBox);

	comPortLayout->addWidget(comPortText);
	comPortLayout->addWidget(comPortBox);

	comboxBoxLayout->addLayout(baudrateLayout);
	comboxBoxLayout->addLayout(comPortLayout);
	comboxBoxLayout->addWidget(portStatus);
	comboxBoxLayout->addWidget(helperText);

	leftLayout->addLayout(comboxBoxLayout);
	leftLayout->addLayout(buttonLayout);

	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(rawReceivedMessageLayout);
	MainMenu->setLayout(mainLayout);

	amountOfComPortChecks->start();
}

QWidget* QSettingsMenu::GetMenu()
{
	return MainMenu;
}

void QSettingsMenu::OnEnter()
{
	// Boi, you're already connected to a com port. We're taking u to the disconnect screen fr.
	if (appRef->arduinoThread.GetArduino()->GetPortState())
	{
		appRef->SetNewQMenu(QMenus::Disconnect);
		return;
	}
}

void QSettingsMenu::OnLeave()
{

}







QStringList GetComPorts()
{
	QStringList result;
	std::vector<std::wstring> ports = GetAvailableComPorts();
	int amountOfSelections = (int)ports.size();
	for (int portIndex = 0; portIndex < ports.size(); ++portIndex)
	{
		// Cuz yk, there's no easy way to put a Wstring to a string
		std::string portAsString(ports[portIndex].begin(), ports[portIndex].end());
		QString port = QString::fromStdString(portAsString);
		result.append(port);
	}
	return result;
}

QStringList GetBaudRates()
{
	QStringList baudrates;
	for (int baudRate = ArduinoBaudRates::_300; baudRate <= ArduinoBaudRates::_115200; baudRate += 100)
	{
		if (VerifyBaudRate(baudRate))
		{
			int baudRateNumber = static_cast<ArduinoBaudRates>(baudRate);
			QString result = QString::number(baudRateNumber);
			baudrates.append(result);
		}
	}
	return baudrates;
}

int QSettingsMenu::GetCurrentBaudRateIndex()
{
	int baudRateIndex = 0;
	for (int baudRate = ArduinoBaudRates::_300; baudRate <= ArduinoBaudRates::_115200; baudRate += 100)
	{
		if (VerifyBaudRate(baudRate))
		{
			if (appRef->arduinoThread.GetArduino()->GetBaudRate() == baudRateIndex)
			{
				std::cout << "Current baudrate is: " << baudRate << std::endl;
				return baudRateIndex;
			}
			baudRateIndex++;
		}
	}
	return 0;
}

int QSettingsMenu::ComPortIndex()
{
	std::vector<std::wstring> ports = GetAvailableComPorts();
	for (int portIndex = 0; portIndex < ports.size(); ++portIndex)
	{
		// Cuz yk, there's no easy way to put a Wstring to a string
		std::string portAsString(ports[portIndex].begin(), ports[portIndex].end());
		if (appRef->arduinoThread.GetArduino()->GetComPort() == portAsString)
		{
			std::cout << "Current port is: " << appRef->arduinoThread.GetArduino()->GetComPort() << std::endl;
			return portIndex;
		}
	}
	return -1;
}



void QSettingsMenu::GoToMainMenu()
{
	appRef->SetNewQMenu(QMenus::MainMenu);
}

void QSettingsMenu::ConnectClicked()
{

}

void QSettingsMenu::BaudRateChanged(int index)
{
	int baudRateIndex = 0;
	for (int baudRate = ArduinoBaudRates::_300; baudRate <= ArduinoBaudRates::_115200; baudRate += 100)
	{
		if (VerifyBaudRate(baudRate))
		{
			if (index == baudRateIndex)
			{
				appRef->arduinoThread.GetArduino()->SetBaudRate(baudRate);
				std::cout << "New baudrate: " << std::to_string(baudRate) << std::endl;
			}
			baudRateIndex++;
		}
	}
}

void QSettingsMenu::SelectedComPortChanged(int index)
{
	QString selectedComPort = comPortBox->itemText(index);
	std::string comPort = selectedComPort.toStdString();
	std::cout << "New Port: " << comPort << std::endl;
	appRef->arduinoThread.GetArduino()->SetComPort(comPort);
}

void QSettingsMenu::ComPortChanged()
{
	static int oldValue = 0;
	int newValue = (int)GetAvailableComPorts().size();

	if (newValue != oldValue)
	{
		oldValue = newValue;

		comPortBox->clear();

		int selectedPort = ComPortIndex();
		comPortBox->addItems(GetComPorts());

		if (selectedPort == -1)
		{
			std::string stdResult = appRef->arduinoThread.GetArduino()->GetComPort();
			QString result = QString::fromStdString(stdResult);
			comPortBox->setCurrentText(result);
		}
		else
		{
			comPortBox->setCurrentIndex(selectedPort);
		}
	}
}