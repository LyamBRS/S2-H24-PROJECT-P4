/**
 * @file Application.h
 * @author LyamBRS
 * @brief 
 * Contains the header definition
 * for the Application class.
 * This class is the only thing that
 * gets executed in main.cpp.
 * @version 0.1
 * @date 2024-02-11
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include "Controller.h"
#include "MuonDetector.h"

// - DEFINES - //

// - CLASS - //

/**
 * @brief 
 * Class used to create the Arduino application
 * that will run and updates controllers based
 * on external PC communications
 */
class Application 
{
    private:
        MuonDetector muonDetector;
        Controller controllerA;
        Controller controllerB;
        bool isConnectedToPC = false;
        /// @brief Each time a comm from the PC is receive, set this to the value that millis() returns.
        int millisecondsAtLastPing = 0;

    public:

        /**
         * @brief Construct a new Application object.
         * This is done in void setup.
         * The only thing void loop should call is
         * Application.UpdateAll();
         */
        Application();

        /**
         * @brief 
         * Resets everything to OFF.
         * @return true:
         * Successfully reset to its default state
         * @return false:
         * Faild to set to a reset state.
         */
        bool Reset();

        /**
         * @brief 
         * Updates the Application object.
         * Updates all the objects within controllers and LCDS
         * @return true:
         * Successfully updated all the aspects of the application
         * @return false:
         * Failed to update all the aspects of the application
         */
        bool UpdateAll();

        /**
         * @brief 
         * Updates the LCD to have the wanted text on it.
         * @attention
         * DO NOT update the LCD ALL THE TIME, the arduino
         * WILL struggle to do that shit.
         * @return true:
         * Successfully updated the LCD with the needed text.
         * @return false:
         * Failed to update the LCD with the needed text.
         */
        bool UpdateLCD();

        /**
         * @brief 
         * Answers the request that was received from the PC.
         * This method also resets the time that it was since
         * the last PC request so that it can successfully
         * detect if it lost connection.
         * @return true:
         * Successfully answered the communication protocol
         * through the teacher's premade JSON whatever library
         * thingy... Could've made our own communication
         * protocol but I guess not...
         * @return false
         * An error occured while answering to the PC.
         */
        bool AnswerCommunicationProtocol();

        /**
         * @brief Get the Time Since Last Communication.
         * Is reset by @ref AnswerCommunicationProtocol.
         * Allows the Application to know if its
         * disconnected from the PC and display a message
         * on the LCD if thats the case.
         * @return int
         * Time in milliseconds
         */
        int GetTimeSinceLastCommunication();
};
