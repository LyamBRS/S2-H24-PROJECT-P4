/**
 * @file Arduino.h
 * @author LyamBRS
 * @brief
 * Contains the header definition of the Arduino
 * class used to handle controllers and the
 * special JSON communication.
 * @version 0.1
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include <iostream>
#include <mutex>
#include "../Controller/Controller.h"
#include "../Communication/Communication.h"
#include "../JSON/json.hpp"
#include "../SimpleTimer/SimpleTimer.h"

// - DEFINES - //
#define ARDUINO_MAX_ATTEMPT_BEFORE_CONNECTION_LOST 50
#define UPDATES_BETWEEN_HANDSHAKES 5

// - JSON ATTRIBUTES - (CA = Communication Attributes)
#define CA_JOYSTICK_X_A "JXA"
#define CA_JOYSTICK_X_B "JXB"
#define CA_JOYSTICK_Y_A "JYA"
#define CA_JOYSTICK_Y_B "JYB"
#define CA_JOYSTICK_BUTTON_A "JBA"
#define CA_JOYSTICK_BUTTON_B "JBB"

#define CA_ACCELEROMETER_X_A "AXA"
#define CA_ACCELEROMETER_X_B "AXB"
#define CA_ACCELEROMETER_Y_A "AYA"
#define CA_ACCELEROMETER_Y_B "AYB"
#define CA_ACCELEROMETER_Z_A "AZA"
#define CA_ACCELEROMETER_Z_B "AZB"

#define CA_TOP_BUTTON_A     "TBA"
#define CA_BOTTOM_BUTTON_A  "BBA"
#define CA_LEFT_BUTTON_A    "LBA"
#define CA_RIGHT_BUTTON_A   "RBA"

#define CA_TOP_BUTTON_B     "TBB"
#define CA_BOTTOM_BUTTON_B  "BBB"
#define CA_LEFT_BUTTON_B    "LBB"
#define CA_RIGHT_BUTTON_B   "RBB"

#define CA_BAR_GRAPH_A      "BGA"
#define CA_BAR_GRAPH_B      "BGB"

#define CA_CONTROLLER_CONNECTED_A "CCA"
#define CA_CONTROLLER_CONNECTED_B "CCB"

#define CA_DETECTED_MUONS   "M"
#define CA_LCD_MESSAGE      "LM"

// - CLASS - //

    enum ArduinoBaudRates
{
    _300    = 300,
    _600    = 600,
    _1200   = 1200,
    _2400   = 2400,
    _4800   = 4800,
    _9600   = 9600,
    _14400  = 14400,
    _19200  = 19200,
    _28800  = 28800,
    _31250  = 31250,
    _38400  = 38400,
    _57600  = 57600,
    _115200 = 115200,
};

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
bool VerifyBaudRate(unsigned int baudRateToverify);

    /**
     * @brief 
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
    class Arduino
    {
        private:
            /// @brief Handles the serial port and JSON objects
            Communication serialHandler;
            /// @brief Vector of controllers that the arduino has.
            std::vector<Controller*> controllers;
            /// @brief How many tries has it been to read a good JSON file?
            int attemptsSinceLastGoodParse = 0;

            int UpdatesBeforeNextHandshake = 0;

            std::string wantedLCDMessage = "  MESSAGE SENT  ";
            std::string lastReceivedMessage = "";
            std::string currentMessage = "";

            Controller controllerA;
            Controller controllerB;

            int detectedMuonCount = 0;

            SimpleTimer timeBetweenChecks = SimpleTimer(5);
            SimpleTimer timeBetweenHandshakes = SimpleTimer(1000);
        
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
            bool GenerateAndSendMessage();

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
            bool ParseReceivedMessage();
        public:
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
            Arduino();

            unsigned int AmountOfTimesSent = 0;

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
            Arduino(std::string arduinoComPort, int arduinoBaudRate);

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
            bool Verify();

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
            Controller* GetPlayerController(int playerIndex);

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
            bool Update();

            std::string GetLastRawMessage();

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
            bool SetNewLCDMessage(std::string newMessage);

            int GetMuonCount();
            bool ResetMuons();

            /**
             * @brief 
             * Returns the current LCD message set to be
             * sent to the arduino.
             * @return std::string 
             */
            std::string GetLCDMessage();

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
            int AmountOfConnectedPlayers();

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
            bool SetComPort(std::string newComPort);

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
            bool SetBaudRate(int newBaudRate);

            /**
             * @brief
             * Returns the current com port that
             * has been selected for the communication.
             * @return std::string 
             */
            std::string GetComPort();

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
            bool GetPortState();

            /**
             * @brief
             * Returns the current baud rate that the
             * arduino is configured at.
             * @return int 
             */
            int GetBaudRate();

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
            bool Connect();

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
            bool Disconnect();

            /**
             * @brief 
             * Takes in messages and appends them
             * @return true:
             * A new message was appended
             * @return false:
             * No message was appended.
             */
            bool HandleMessageReception();
    };