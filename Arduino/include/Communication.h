/**
 * @file Communication.h
 * @author LyamBRS, Jean-Samuel Lauzon 
 * @brief 
 * File containing header definitions used to
 * handle and create the Communication class
 * which uses libraries given by teachers
 * grouped under a convinient class.
 * @version 0.1
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */
#pragma once

// - INCLUDES - //
#include <Arduino.h>
#include <ArduinoJson.h>
#include "Controller.h"
#include "MuonDetector.h"
#include "SimpleTimer.h"
#include "string.h"

// - DEFINES - //
#define BAUD 115200

// - ERROR MESSAGES - (CE = Communication errors)
#define MS_BEFORE_CONNECTION_LOST        1000
#define CE_SERIAL_NOT_SETUP              "Serial undefined"
#define CE_PARSING_FAILED                "RX parsing error"
#define CE_CONTROLLER_LINKAGE_FAILURE    "Controller nlink"
#define CE_COMMUNICATION_LOST            "Connection lost "
#define CE_NO_ERRORS                     "                "
#define CE_FAILURE_TO_SEND_MESSAGE       "TX error        "
#define CE_MUON_DETECTOR_LINKAGE_FAILURE "Muon not linked "

// - JSON ATTRIBUTES - (CA = Communication Attributes)
#define CA_JOYSTICK_X_A "JXA"
#define CA_JOYSTICK_X_B "JXB"
#define CA_JOYSTICK_Y_A "JYA"
#define CA_JOYSTICK_Y_B "JYB"
#define CA_JOYSTICK_BUTTON_A "JBA"
#define CA_JOYSTICK_BUTTON_B "JBB"

#define CA_ACCELEROMETER_X_A "AXA"
#define CA_ACCELEROMETER_X_B "AXA"
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
/**
 * @brief 
 * Class used to create a simple handler that
 * utilises JSON to establish and answer data
 * requests from the PC that is connected to
 * the Arduino. This class is simply an easy
 * to understand, abstraction layer seperating
 * the messy original program from the Arduino's
 * main program.
 */
class Communication
{
    private:
        /// @brief Flag raised when the class determines that a message should be sent to the PC
        volatile bool shouldSend_ = false;
        /// @brief Flag raised when the class determines that a message was received.
        volatile bool shouldRead_ = false;

        String errorMessage = CE_NO_ERRORS;
        String currentMessage = "";
        SimpleTimer timeBetweenReadChecks = SimpleTimer(2);

        MuonDetector* randomMuonDetector;
        Controller* controllerPlayerA;
        Controller* controllerPlayerB;

        String PCMessage = "NO MESSAGE RX   ";

        bool controllersLinked = false;
        bool serialSetUp = false;
        bool muonDetectorLinked = false;

        int oldAmountOfCharacters = 0;
        int currentAmountOfCharacters = 0;

        /// @brief Keeps track of how long it has been since a message was received.
        int millisWhenLastRead = 0;

        /**
         * @brief 
         * Simple private function that reads
         * the data that is available on the
         * serial port and parses it into JSON
         * formats allowing us to later read it
         * normally without issues.
         * @return true:
         * Successfully parsed received message
         * into the class.
         * @return false:
         * Failed to parse the received message
         * into the class.
         */
        bool ParseReceivedMessage();

        /**
         * @brief 
         * Method executed when the program needs
         * to send a reply back to the PC. This
         * should be executed right after message
         * received @ref ParseReceivedMessage is
         * successfully executed.
         * @return true:
         * Successfully replied a message to the
         * PC
         * @return false:
         * Failed to reply a message to the PC.
         */
        bool SendMessage(); 
    public:

        /**
         * @brief Construct a new Communication object.
         * Should be done in main.cpp as a global
         * object available both to void setup and void
         * loop.
         */
        Communication();

        /**
         * @brief 
         * Starts Arduino serial class associated
         * with the communication protocol.
         * @param baudRate
         * Communication speeds.
         * @return true:
         * Successfully started the serial.
         * @return false:
         * Failed to start the serial.
         */
        bool StartSerial(unsigned long baudRate);

        /**
         * @brief 
         * Gives the communication class a reference
         * to the 2 remote controllers that can be
         * connected to this Arduino. This way the
         * communication class can easily build the
         * message that it needs to send to the PC
         * based on the Controllers values as well
         * as set the components on the remotes to
         * wanted values.
         * @attention
         * This needs to be executed in void setup.
         * @param controllerA
         * Controller associated with player A
         * @param controllerB
         * Controller associated with player B
         * @return true:
         * Successfully linked controllers to the
         * communication class.
         * @return false:
         * Failed to link controllers.
         */
        bool LinkControllers(Controller* controllerA, Controller* controllerB);

        /**
         * @brief 
         * Links the muon detector to the communication
         * class allowing it to build TX messages with
         * its parameters inside.
         * @attention
         * MUST BE CALLED IN VOID SETUP
         * @param muonDetector
         * Muon detector class to link with the
         * communication class.
         * @return true:
         * Successfully linked the muon detector.
         * @return false:
         * Failed to link the muon detector.
         */
        bool LinkMuonDetector(MuonDetector* muonDetector);

        /**
         * @brief 
         * Method that should be executed along with
         * all the update methods of the program.
         */
        void Update();

        /**
         * @brief
         * Function that is required to be called
         * in @ref serialEvent
         */
        void SerivalEventHandler();

        /**
         * @brief
         * Tells you if there is an ongoing
         * communication problem of any sorts.
         * @attention
         * Error messages will always be 20 chars
         * long.
         * @return string 
         */
        String GetErrorMessage();

        /**
         * @brief 
         * Tells you if a message was received and if it was
         * appended.
         * @return true:
         * A message was appended.
         * @return false:
         * No message was appended.
         */
        bool HasReceivedAMessage();

        /**
         * @brief 
         * Returns the message that the PC wants written on
         * the LCD of the arduino.
         */
        String GetPCMessage();
};