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
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "Controller.h"
#include "MuonDetector.h"
#include "Communication.h"


// - DEFINES - //

//const int rs = 34, en = 32, d4 = 30, d5 =28, d6 = 26, d7 = 24;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define PIN_LCD_RS 34
#define PIN_LCD_EN 32
#define PIN_LCD_D4 30
#define PIN_LCD_D5 28
#define PIN_LCD_D6 26
#define PIN_LCD_D7 24

#define PIN_MUON 0

#define PIN_CONTROLLER_A_DETECTION 0
#define PIN_CONTROLLER_B_DETECTION 0

#define PIN_CONTROLLER_A_HEARTHBEAT 0
#define PIN_CONTROLLER_B_HEARTHBEAT 0

#define PIN_CONTROLLER_A_JOY_BUTTON 0
#define PIN_CONTROLLER_A_TOP_BUTTON 0
#define PIN_CONTROLLER_A_BOT_BUTTON 0
#define PIN_CONTROLLER_A_L_BUTTON 0
#define PIN_CONTROLLER_A_R_BUTTON 0

#define PIN_CONTROLLER_B_JOY_BUTTON 0
#define PIN_CONTROLLER_B_TOP_BUTTON 0
#define PIN_CONTROLLER_B_BOT_BUTTON 0
#define PIN_CONTROLLER_B_L_BUTTON 0
#define PIN_CONTROLLER_B_R_BUTTON 0

#define PIN_CONTROLLER_A_BARGRAPH_A 44
#define PIN_CONTROLLER_A_BARGRAPH_B 38
#define PIN_CONTROLLER_A_BARGRAPH_C 40
#define PIN_CONTROLLER_A_BARGRAPH_D 36
#define PIN_CONTROLLER_A_BARGRAPH_E 42
#define PIN_CONTROLLER_A_BARGRAPH_F 45
#define PIN_CONTROLLER_A_BARGRAPH_G 43
#define PIN_CONTROLLER_A_BARGRAPH_H 41
#define PIN_CONTROLLER_A_BARGRAPH_I 39
#define PIN_CONTROLLER_A_BARGRAPH_J 37

#define PIN_CONTROLLER_B_BARGRAPH_A 0
#define PIN_CONTROLLER_B_BARGRAPH_B 0
#define PIN_CONTROLLER_B_BARGRAPH_C 0
#define PIN_CONTROLLER_B_BARGRAPH_D 0
#define PIN_CONTROLLER_B_BARGRAPH_E 0
#define PIN_CONTROLLER_B_BARGRAPH_F 0
#define PIN_CONTROLLER_B_BARGRAPH_G 0
#define PIN_CONTROLLER_B_BARGRAPH_H 0
#define PIN_CONTROLLER_B_BARGRAPH_I 0
#define PIN_CONTROLLER_B_BARGRAPH_J 0

#define PIN_CONTROLLER_A_JOY_X 0
#define PIN_CONTROLLER_A_JOY_Y 0

#define PIN_CONTROLLER_B_JOY_X 0
#define PIN_CONTROLLER_B_JOY_Y 0

#define PIN_CONTROLLER_A_ACCELEROMETER_X 0
#define PIN_CONTROLLER_A_ACCELEROMETER_Y 0
#define PIN_CONTROLLER_A_ACCELEROMETER_Z 0

#define PIN_CONTROLLER_B_ACCELEROMETER_X 0
#define PIN_CONTROLLER_B_ACCELEROMETER_Y 0
#define PIN_CONTROLLER_B_ACCELEROMETER_Z 0

// - LCD - //

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
        MuonDetector* muonDetector;
        Controller* controllerA;
        Controller* controllerB;
        Communication communication;
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
         * Sets up the entire application.
         * This needs to be called in void setup.
         * @return true:
         * Successfully created the application.
         * @return false:
         * Failed to create the application.
         */
        bool Setup();

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
