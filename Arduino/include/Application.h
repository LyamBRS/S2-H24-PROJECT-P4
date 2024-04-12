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

#define PIN_LCD_RS 35
#define PIN_LCD_EN 33
#define PIN_LCD_D4 31
#define PIN_LCD_D5 29
#define PIN_LCD_D6 27
#define PIN_LCD_D7 25

#define PIN_MUON A0

#define PIN_CONTROLLER_A_DETECTION 2
#define PIN_CONTROLLER_B_DETECTION 10

#define PIN_CONTROLLER_A_HEARTHBEAT 44
#define PIN_CONTROLLER_B_HEARTHBEAT 23

#define PIN_CONTROLLER_A_JOY_BUTTON 42
#define PIN_CONTROLLER_A_TOP_BUTTON 24
#define PIN_CONTROLLER_A_BOT_BUTTON 26
#define PIN_CONTROLLER_A_L_BUTTON 22
#define PIN_CONTROLLER_A_R_BUTTON 28

#define PIN_CONTROLLER_B_JOY_BUTTON 9
#define PIN_CONTROLLER_B_TOP_BUTTON 7
#define PIN_CONTROLLER_B_BOT_BUTTON 5
#define PIN_CONTROLLER_B_L_BUTTON 6
#define PIN_CONTROLLER_B_R_BUTTON 8

#define PIN_CONTROLLER_A_BARGRAPH_A 46
#define PIN_CONTROLLER_A_BARGRAPH_B 48
#define PIN_CONTROLLER_A_BARGRAPH_C 50
#define PIN_CONTROLLER_A_BARGRAPH_D 52
#define PIN_CONTROLLER_A_BARGRAPH_E 43
#define PIN_CONTROLLER_A_BARGRAPH_F 45
#define PIN_CONTROLLER_A_BARGRAPH_G 47
#define PIN_CONTROLLER_A_BARGRAPH_H 49
#define PIN_CONTROLLER_A_BARGRAPH_I 51
#define PIN_CONTROLLER_A_BARGRAPH_J 53

#define PIN_CONTROLLER_B_BARGRAPH_A 30
#define PIN_CONTROLLER_B_BARGRAPH_B 32
#define PIN_CONTROLLER_B_BARGRAPH_C 34
#define PIN_CONTROLLER_B_BARGRAPH_D 36
#define PIN_CONTROLLER_B_BARGRAPH_E 38
#define PIN_CONTROLLER_B_BARGRAPH_F 40
#define PIN_CONTROLLER_B_BARGRAPH_G 37
#define PIN_CONTROLLER_B_BARGRAPH_H 39
#define PIN_CONTROLLER_B_BARGRAPH_I 41
#define PIN_CONTROLLER_B_BARGRAPH_J 4

#define PIN_CONTROLLER_A_JOY_X A15
#define PIN_CONTROLLER_A_JOY_Y A14

#define PIN_CONTROLLER_B_JOY_X A10
#define PIN_CONTROLLER_B_JOY_Y A9

#define PIN_CONTROLLER_A_ACCELEROMETER_X A11
#define PIN_CONTROLLER_A_ACCELEROMETER_Y A12
#define PIN_CONTROLLER_A_ACCELEROMETER_Z A13

#define PIN_CONTROLLER_B_ACCELEROMETER_X A6
#define PIN_CONTROLLER_B_ACCELEROMETER_Y A7
#define PIN_CONTROLLER_B_ACCELEROMETER_Z A8

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
