/**
 * @file Arduino.cpp
 * @author LyamBRS
 * @brief
 * File containing the methods
 * used in the Arduino class
 * defined in @ref Arduino.h
 * @version 0.1
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "../Arduino/Arduino.h"

/**
 * @brief
 * # VerifyBaudRate
 * @brief 
 * Returns true or false depending on the
 * validity of the input baud rate. The
 * baud rate must be within
 * @ref ArduinoBaudRates to be valid.
 * @param baudRateToverify 
 * @return true 
 * @return false 
 */
bool VerifyBaudRate(unsigned int baudRateToverify)
{
    switch(baudRateToverify)
    {
        case(ArduinoBaudRates::_115200):
        case(ArduinoBaudRates::_57600):
        case(ArduinoBaudRates::_38400):
        case(ArduinoBaudRates::_31250):
        case(ArduinoBaudRates::_28800):
        case(ArduinoBaudRates::_14400):
        case(ArduinoBaudRates::_19200):
        case(ArduinoBaudRates::_9600):
        case(ArduinoBaudRates::_4800):
        case(ArduinoBaudRates::_2400):
        case(ArduinoBaudRates::_1200):
        case(ArduinoBaudRates::_600):
        case(ArduinoBaudRates::_300):
            return true;
    }
    return false;
}

/**
 * @brief 
 * Generates a JSON text file to send on the Arduino's
 * serial port. The JSON file is generated based on
 * @ref Controller values.
 * @return true:
 * Successfully generated the JSON file and sent it.
 * @return false:
 * Failed to do the task.
 */
bool Arduino::GenerateAndSendMessage()
{
    std::lock_guard<std::mutex> lock(mutex);
    if(!serialHandler.ConnectionStatus())
    {
        std::cerr << "Attempted to send a message while connection is not established" << std::endl;
        Disconnect();
        return false;
    }

    nlohmann::json jsonToSend;

    jsonToSend[CA_LCD_MESSAGE] = wantedLCDMessage;
    jsonToSend[CA_BAR_GRAPH_A] = controllers[0]->barGraphBits;
    jsonToSend[CA_BAR_GRAPH_B] = controllers[1]->barGraphBits;

    if(!serialHandler.SendToSerial(jsonToSend))
    {
        std::cerr << "Failure while trying to send JSON to the serial port." << std::endl;
        Disconnect();
        return false;
    }
    return true;
}

/**
 * @brief 
 * Takes a received string from the @ref Communication
 * class and parses it as a JSON file to parse the
 * various inputs into their respective @ref Controller
 * classes.
 * @return true:
 * Successfully parsed the message into the Controllers 
 * @return false:
 * Failed to parse the message into the Controllers.
 */
bool Arduino::ParseReceivedMessage()
{
    std::lock_guard<std::mutex> lock(mutex);
    if(!serialHandler.ConnectionStatus())
    {
        std::cerr << "Attempted to parse a message while connection is not established" << std::endl;
        Disconnect();
        return false;
    }

    std::string receivedMessage;
    nlohmann::json jsonToParse;
    jsonToParse.clear();

    if(!serialHandler.GetSerialMessage(receivedMessage))
    {
        std::cerr << "Failed to get a message back from serial port" << std::endl;
        return false;
    }

    if(receivedMessage.size() == 0)
    {
        // Not necessarly an error ofc.
        return false;
    }
    lastReceivedMessage = receivedMessage;
    jsonToParse = nlohmann::json::parse(receivedMessage, nullptr, false);
    if(jsonToParse.is_discarded())
    {
        return false;
    }


    // - PARSING - // (Yes I know, I shouldve made a function for that + I shouldve made enums to for loop and parse everything in one go. Bowomp.)

    if(!jsonToParse.is_array() && !jsonToParse.is_structured())
    {
        return false;
    }

    // - ACCELEROMETER - //
    if(!jsonToParse[CA_ACCELEROMETER_X_A].is_null())    controllers[0]->accelerometerX = jsonToParse[CA_ACCELEROMETER_X_A].template get<int>(); else controllers[0]->accelerometerX = -1;
    if(!jsonToParse[CA_ACCELEROMETER_Y_A].is_null())    controllers[0]->accelerometerY = jsonToParse[CA_ACCELEROMETER_Y_A].template get<int>(); else controllers[0]->accelerometerY = -1;
    if(!jsonToParse[CA_ACCELEROMETER_Z_A].is_null())    controllers[0]->accelerometerZ = jsonToParse[CA_ACCELEROMETER_Z_A].template get<int>(); else controllers[0]->accelerometerZ = -1;
    
    if(!jsonToParse[CA_ACCELEROMETER_X_B].is_null())    controllers[1]->accelerometerX = jsonToParse[CA_ACCELEROMETER_X_B].template get<int>(); else controllers[1]->accelerometerX = -1;
    if(!jsonToParse[CA_ACCELEROMETER_Y_B].is_null())    controllers[1]->accelerometerY = jsonToParse[CA_ACCELEROMETER_Y_B].template get<int>(); else controllers[1]->accelerometerY = -1;
    if(!jsonToParse[CA_ACCELEROMETER_Z_B].is_null())    controllers[1]->accelerometerZ = jsonToParse[CA_ACCELEROMETER_Z_B].template get<int>(); else controllers[1]->accelerometerZ = -1;

    // - JOYSTICK - //
    if(!jsonToParse[CA_JOYSTICK_X_A].is_null())         controllers[0]->joystickX = jsonToParse[CA_JOYSTICK_X_A].template get<int>(); else controllers[0]->joystickX = -1;
    if(!jsonToParse[CA_JOYSTICK_Y_A].is_null())         controllers[0]->joystickY = jsonToParse[CA_JOYSTICK_Y_A].template get<int>(); else controllers[0]->joystickY = -1;
    if(!jsonToParse[CA_JOYSTICK_BUTTON_A].is_null())    controllers[0]->joystickButton = jsonToParse[CA_JOYSTICK_BUTTON_A].template get<int>(); else controllers[0]->joystickButton = -1;
    
    if(!jsonToParse[CA_JOYSTICK_X_B].is_null())         controllers[1]->joystickX = jsonToParse[CA_JOYSTICK_X_B].template get<int>(); else controllers[1]->joystickX = -1;
    if(!jsonToParse[CA_JOYSTICK_Y_B].is_null())         controllers[1]->joystickY = jsonToParse[CA_JOYSTICK_Y_B].template get<int>(); else controllers[1]->joystickY = -1;
    if(!jsonToParse[CA_JOYSTICK_BUTTON_B].is_null())    controllers[1]->joystickButton = jsonToParse[CA_JOYSTICK_BUTTON_B].template get<bool>(); else controllers[1]->joystickButton = false;

    // - BUTTONS - //
    if(!jsonToParse[CA_BOTTOM_BUTTON_A].is_null())      controllers[0]->bottomButton = jsonToParse[CA_BOTTOM_BUTTON_A].template get<bool>(); else controllers[0]->bottomButton = false;
    if(!jsonToParse[CA_TOP_BUTTON_A].is_null())         controllers[0]->topButton = jsonToParse[CA_TOP_BUTTON_A].template get<bool>(); else controllers[0]->topButton = false;
    if(!jsonToParse[CA_RIGHT_BUTTON_A].is_null())       controllers[0]->rightButton = jsonToParse[CA_RIGHT_BUTTON_A].template get<bool>(); else controllers[0]->rightButton = false;
    if(!jsonToParse[CA_LEFT_BUTTON_A].is_null())        controllers[0]->leftButton = jsonToParse[CA_LEFT_BUTTON_A].template get<bool>(); else controllers[0]->leftButton = false;
    
    if(!jsonToParse[CA_BOTTOM_BUTTON_B].is_null())      controllers[1]->bottomButton = jsonToParse[CA_BOTTOM_BUTTON_B].template get<bool>(); else controllers[1]->bottomButton = false;
    if(!jsonToParse[CA_TOP_BUTTON_B].is_null())         controllers[1]->topButton = jsonToParse[CA_TOP_BUTTON_B].template get<bool>(); else controllers[1]->topButton = false;
    if(!jsonToParse[CA_RIGHT_BUTTON_B].is_null())       controllers[1]->rightButton = jsonToParse[CA_RIGHT_BUTTON_B].template get<bool>(); else controllers[1]->rightButton = false;
    if(!jsonToParse[CA_LEFT_BUTTON_B].is_null())        controllers[1]->leftButton = jsonToParse[CA_LEFT_BUTTON_B].template get<bool>(); else controllers[1]->leftButton = false;

    // - BAR GRAPHS - //
    if(!jsonToParse[CA_BAR_GRAPH_A].is_null())          controllers[0]->barGraphBits = jsonToParse[CA_BAR_GRAPH_A].template get<int>(); else controllers[0]->barGraphBits = -1;
    if(!jsonToParse[CA_BAR_GRAPH_B].is_null())          controllers[1]->barGraphBits = jsonToParse[CA_BAR_GRAPH_B].template get<int>(); else controllers[1]->barGraphBits = -1;

    // - CONNECTION - //
    if(!jsonToParse[CA_CONTROLLER_CONNECTED_A].is_null())          controllers[0]->isConnected = jsonToParse[CA_CONTROLLER_CONNECTED_A].template get<bool>(); else controllers[0]->isConnected = false;
    if(!jsonToParse[CA_CONTROLLER_CONNECTED_B].is_null())          controllers[1]->isConnected = jsonToParse[CA_CONTROLLER_CONNECTED_B].template get<bool>(); else controllers[1]->isConnected = false;

    return true;
}

std::string Arduino::GetLastRawMessage()
{
    std::lock_guard<std::mutex> lock(mutex);
    return lastReceivedMessage;
}

/**
 * @brief Construct a new Arduino object.
 * Class used to handle an arduino where 2 simple
 * controllers can connect to. This arduino communicates
 * with the PC through a "communication" protocol if it
 * can be called that allowing JSON files to be exchanged
 * between the two. The arduino will send controller
 * informations on the serial port to the PC and the PC
 * will send LCD and BarGraph information to the arduino.
 * The PC is the one to initate the handshake with the
 * arduino.
 */
Arduino::Arduino()
{
    std::lock_guard<std::mutex> lock(mutex);
    Controller controllerA = Controller();
    Controller controllerB = Controller();

    controllers.push_back(&controllerA);
    controllers.push_back(&controllerB);
}

/**
 * @brief Construct a new Arduino object.
 * Class used to handle an arduino where 2 simple
 * controllers can connect to. This arduino communicates
 * with the PC through a "communication" protocol if it
 * can be called that allowing JSON files to be exchanged
 * between the two. The arduino will send controller
 * informations on the serial port to the PC and the PC
 * will send LCD and BarGraph information to the arduino.
 * The PC is the one to initate the handshake with the
 * arduino.
 * @param arduinoComPort
 * Which com port is the arduino supposed to be at.
 * @param arduinoBaudRate
 * Which baud rate is the arduino supposed to be
 * using.
 */
Arduino::Arduino(std::string arduinoComPort, int arduinoBaudRate)
{
    std::lock_guard<std::mutex> lock(mutex);
    serialHandler.SetBaudRate(arduinoBaudRate);
    serialHandler.SetComPort(arduinoComPort);

    Controller controllerA = Controller();
    Controller controllerB = Controller();

    controllers.push_back(&controllerA);
    controllers.push_back(&controllerB);
}

/**
 * @brief 
 * Method that allows you to check if the Arduino
 * has been responding according to plan. This
 * will check wether the com port is connected at
 * all and will also tell you if its been a while
 * since a JSON file was successfully parsed from
 * the arduino.
 * @return true:
 * Everything is working well! 
 * @return false:
 * No ports opened / Nothing answered for a while.
 */
bool Arduino::Verify()
{
    std::lock_guard<std::mutex> lock(mutex);
    if(!serialHandler.ConnectionStatus()) return false;
    if(attemptsSinceLastGoodParse > ARDUINO_MAX_ATTEMPT_BEFORE_CONNECTION_LOST) return false;

    return true;
}

/**
 * @brief
 * Returns a player's controller so that you can
 * modify, get and change values of that controller.
 * Some values are automatically overwritten when a
 * new JSON file is seen from the arduino such as
 * inputs. Others will be sent to the arduino when
 * an handshake next occurs.
 * @attention
 * ## IF INDEX OUT OF BOUNDS, IT WILL BE 0.
 * @param playerIndex
 * Which controller do you want?
 * @return Controller* 
 */
Controller* Arduino::GetPlayerController(int playerIndex)
{
    std::lock_guard<std::mutex> lock(mutex);
    if(playerIndex > 1) playerIndex = 0;
    return controllers[playerIndex];
}

/**
 * @brief
 * Only tells you if the serial port is connected
 * on the PC side of things. Use @ref Verify to
 * ensure that it is truly working as intended.
 * @return true:
 * SerialPort is connected.
 * @return false:
 * SerialPort is not connected.
 */
bool Arduino::GetPortState()
{
    std::lock_guard<std::mutex> lock(mutex);
    return serialHandler.ConnectionStatus();
}

/**
 * @brief 
 * Update function of the Arduino object.
 * This handles the handshakes, communications,
 * JSON buildings n so on. This is used to
 * determine the intervals at which handshakes
 * must be sent n shit.
 * @return true:
 * Successfully updated everything.
 * @return false:
 * Welp, I guess something went wrong eh?
 */
bool Arduino::Update()
{
    if(serialHandler.ConnectionStatus())
    {
        UpdatesBeforeNextHandshake--;
        if(UpdatesBeforeNextHandshake <= 0)
        {
            UpdatesBeforeNextHandshake = UPDATES_BETWEEN_HANDSHAKES;
            if(GenerateAndSendMessage())
            {
                attemptsSinceLastGoodParse++;
                //return true;
            }
        }

        if(ParseReceivedMessage())
        {
            attemptsSinceLastGoodParse = 0;
            //return true;
        }
    }
    return false;
}

/**
 * @brief Set the New LCD Message.
 * The string MUST be 20 or below characters.
 * You only have access to one line on the
 * LCD.
 * @param newMessage
 * New 20 character message to display on the
 * arduino screen
 * @return true:
 * Message is valid and ready to be sent
 * in the next handshake.
 * @return false:
 * Invalid message bruh
 */
bool Arduino::SetNewLCDMessage(std::string newMessage)
{
    std::lock_guard<std::mutex> lock(mutex);
    if(newMessage.length() > 20)
    {
        return false;
    }
    wantedLCDMessage = newMessage;
    return true;
}

/**
 * @brief 
 * Returns the current LCD message set to be
 * sent to the arduino.
 * @return std::string 
 */
std::string Arduino::GetLCDMessage()
{
    std::lock_guard<std::mutex> lock(mutex);
    return wantedLCDMessage;
}

/**
 * @brief 
 * Tells you how many controllers are currently
 * responding on the Arduino. To see which
 * controller specifically, you MUST obtain the
 * pointer to each and check their member
 * attributes. Controllers that are not connected
 * should be reset and players should stop
 * moving around like headless chickens.
 * @return int
 * -1 = ERROR
 */
int Arduino::AmountOfConnectedPlayers()
{
    std::lock_guard<std::mutex> lock(mutex);
    int total = 0;
    for(int index=0; index < controllers.size(); ++index)
    {
        Controller* controller = controllers[index];
        if(controller->isConnected) total++;
    }
    return total;
}

/**
 * @brief Set the Com Port of the arduino.
 * Can only be done when the Arduino is
 * disconnected.
 * 
 * @param newComPort
 * New com port for the Arduino to use
 * to communicate.
 * @return true:
 * Successfully changed the com port.
 * @return false:
 * Failed to change the com port.
 */
bool Arduino::SetComPort(std::string newComPort)
{
    std::lock_guard<std::mutex> lock(mutex);
    return serialHandler.SetComPort(newComPort);
}

/**
 * @brief Set the Baud Rate.
 * Sets the baud rate of the arduino's serial
 * port, defining the speed at which the
 * program will attempt to communicate with
 * the Arduino. Yes they both need to be the
 * same. Yes its probably why you're reading
 * gibberish on your terminal.
 * @param newBaudRate
 * new baudrate value that the port should use.
 * @return true:
 * Successfully updated the baud rate.
 * @return false:
 * Failed to update the baud rate to that value.
 */
bool Arduino::SetBaudRate(int newBaudRate)
{
    std::lock_guard<std::mutex> lock(mutex);
    return serialHandler.SetBaudRate(newBaudRate);
}

/**
 * @brief
 * Returns the current com port that
 * has been selected for the communication.
 * @return std::string 
 */
std::string Arduino::GetComPort()
{
    std::lock_guard<std::mutex> lock(mutex);
    return serialHandler.GetComPort();
}

/**
 * @brief
 * Returns the current baud rate that the
 * arduino is configured at.
 * @return int 
 */
int Arduino::GetBaudRate()
{
    std::lock_guard<std::mutex> lock(mutex);
    return serialHandler.GetBaudRate();
}

/**
 * @brief 
 * Attempts to connect the serial port to the
 * specified values set either through methods
 * or in the constructor when the object was
 * built.
 * @attention
 * ## THIS WILL FREEZE THE APPLICATION AS IT CONNECTS
 * @return true 
 * @return false 
 */
bool Arduino::Connect()
{
    std::lock_guard<std::mutex> lock(mutex);
    return serialHandler.Connect();
}

/**
 * @brief 
 * Disconnects the arduino from the serial port
 * allowing its values to be changed for example.
 * @return true:
 * Successfully disconnected the arduino.
 * @return false:
 * Failed to disconnect the arduino / arduino
 * already disconnected.
 */
bool Arduino::Disconnect()
{
    std::lock_guard<std::mutex> lock(mutex);
    return serialHandler.Disconnect();
}