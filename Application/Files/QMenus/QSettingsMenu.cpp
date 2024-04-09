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

	CreateTimers();
	CreateWidgets();
	CreateLayouts();
	ConnectWidgets();
	CreateMenu();

	// - LABEL SETUPS - //


	// - LAYOUT SETUPS - //


	// - SIGNALS & SLOTS - CONNECTION - //

	// - LAYOUT MAKING AND WIDGET ARRANGEMENTS - //

}


void QSettingsMenu::CreateTimers()
{
	// - CREATE
	amountOfComPortChecks = new QTimer();
	connectingProgress = new QTimer();

	// - SET
	amountOfComPortChecks->setInterval(500);
	connectingProgress->setInterval(100);

	// - START
	amountOfComPortChecks->start();
}

void QSettingsMenu::CreateWidgets()
{
	MainMenu	= new QWidget();
	leftArea	= new QWidget();
	rightArea	= new QWidget();

	backButton		= new QPushButton("Back");
	connectButton	= new QPushButton("Connect");

	baudratesBox	= new QComboBox();
	comPortBox		= new CustomComboBox();

	connectionProgress = new QProgressBar();
	connectionProgress->setRange(0, 100);
	connectionProgress->setEnabled(false);

	baudRateText			= new QLabel("Baudrate:");
	comPortText				= new QLabel("Port:");
	helperText				= new QLabel("helperText");
	portStatus				= new QLabel("Port status");
	rawReceivedMessageText	= new QLabel("ARDUINO MESSAGE IS SEEN HERE");

	rawReceivedMessageText->setStyleSheet("border: 1px solid black;");
	rawReceivedMessageText->setWordWrap(true);
	helperText->setAlignment(Qt::AlignCenter);
	portStatus->setAlignment(Qt::AlignCenter);

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

	// - SET WANTED LOOKS FOR STUFF - //
	if (appRef->arduinoThread.GetArduino()->GetPortState())
	{
		connectButton->setText("Disconnect");
		baudratesBox->setEnabled(false);
		comPortBox->setEnabled(false);
	}
}

void QSettingsMenu::CreateLayouts()
{
	buttonLayout				= new QVBoxLayout();
	comboxBoxLayout				= new QVBoxLayout();
	rawReceivedMessageLayout	= new QVBoxLayout();
	leftLayout					= new QVBoxLayout();

	baudrateLayout	= new QHBoxLayout();
	comPortLayout	= new QHBoxLayout();

	mainLayout = new QGridLayout();
}

void QSettingsMenu::ConnectWidgets()
{
	connect(backButton,		&QPushButton::clicked, this, &QSettingsMenu::GoToMainMenu);
	connect(connectButton,	&QPushButton::clicked, this, &QSettingsMenu::ConnectClicked);

	connect(baudratesBox,	QOverload<int>::of(&QComboBox::currentIndexChanged), this, &QSettingsMenu::BaudRateChanged);
	connect(comPortBox,		QOverload<int>::of(&QComboBox::currentIndexChanged), this, &QSettingsMenu::SelectedComPortChanged);

	connect(amountOfComPortChecks,	&QTimer::timeout, this, &QSettingsMenu::ComPortChanged);
	connect(connectingProgress,		&QTimer::timeout, this, &QSettingsMenu::CheckOnConnectionStatus);
}

void QSettingsMenu::CreateMenu()
{
	buttonLayout->addWidget(connectButton);
	buttonLayout->addWidget(backButton);
	buttonLayout->addWidget(connectionProgress);

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

	leftArea->setLayout(leftLayout);
	rightArea->setLayout(rawReceivedMessageLayout);

	mainLayout->addWidget(leftArea, 0, 0, 50, 50);
	mainLayout->addWidget(rightArea, 0, 51, 50, 50);
	MainMenu->setLayout(mainLayout);
}





QWidget* QSettingsMenu::GetMenu()
{
	return MainMenu;
}

void QSettingsMenu::OnEnter()
{
	// Boi, you're already connected to a com port. We're taking u to the disconnect screen fr.
	//if (appRef->arduinoThread.GetArduino()->GetPortState())
	//{
	//	appRef->SetNewQMenu(QMenus::Disconnect);
	//	return;
	//}
}

void QSettingsMenu::OnLeave()
{
	amountOfComPortChecks->stop();
	connectingProgress->stop();
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
	std::cout << "Baudrate is: " << appRef->arduinoThread.GetArduino()->GetBaudRate() << std::endl;
	for (int baudRate = ArduinoBaudRates::_300; baudRate <= ArduinoBaudRates::_115200; baudRate += 100)
	{
		if (VerifyBaudRate(baudRate))
		{
			if (appRef->arduinoThread.GetArduino()->GetBaudRate() == baudRate)
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
	if (appRef->arduinoThread.GetArduino()->GetPortState())
	{
		appRef->arduinoThread.GetArduino()->Disconnect();
		connectButton->setText("Connect");
		baudratesBox->setEnabled(true);
		comPortBox->setEnabled(true);
		helperText->setText("Successfully disconnected");
		return;
	}
	connectingProgress->stop();
	connectingProgress->start();
	connectButton->setEnabled(false);
	connectionProgress->setEnabled(true);
	connectionProgress->setValue(0);
	appRef->arduinoThread.GetArduino()->Connect();
	helperText->setText("Connecting...");
}

void QSettingsMenu::CheckOnConnectionStatus()
{
	int newValue = connectionProgress->value() + 10;
	if (newValue > connectionProgress->maximum()) {
		
		// Connection failure
		connectButton->setEnabled(true);
		connectionProgress->setEnabled(false);
		helperText->setText("Failed to connect with specified parameters");
		connectingProgress->stop();
		return;
	}
	connectionProgress->setValue(newValue);

	if (appRef->arduinoThread.GetArduino()->GetPortState())
	{
		helperText->setText("Successfully connected!");
		connectionProgress->setEnabled(false);

		connectButton->setText("Disconnect");
		connectButton->setEnabled(true);
		baudratesBox->setEnabled(false);
		comPortBox->setEnabled(false);
		connectingProgress->stop();
		connectionProgress->setValue(100);
	}
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

	std::string rawMessage = appRef->arduinoThread.GetArduino()->GetLastRawMessage();
	QString result = QString::fromStdString(rawMessage);
	rawReceivedMessageText->setText(result);

	if (!appRef->arduinoThread.GetArduino()->GetPortState()) portStatus->setText("No arduino connected to the PC");
	if (appRef->arduinoThread.GetArduino()->GetPortState() && !appRef->arduinoThread.GetArduino()->Verify()) portStatus->setText("Connected devices not answering requests");
	if (appRef->arduinoThread.GetArduino()->GetPortState() && appRef->arduinoThread.GetArduino()->Verify())  portStatus->setText("Connected arduino is operational");
}