/**
 * @file Application.cpp
 * @author LyamBRS
 * @brief 
 * Contains the header definition
 * for the Application class.
 * This class is the only thing that
 * gets executed in main.cpp.
 * @version 0.1
 * @date 2024-02-27
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "Application.h"

// - DEFINES - //

// - CLASS - //

// - LCD - //
#ifndef LCDCLASS
#define LCDCLASS
const int 
rs = PIN_LCD_RS, // register select
en = PIN_LCD_EN, // Enable
d4 = PIN_LCD_D4, //data pins
d5 = PIN_LCD_D5,
d6 = PIN_LCD_D6,
d7 = PIN_LCD_D7;
 LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#endif

/**
 * @brief Construct a new Application object.
 * This is done in void setup.
 * The only thing void loop should call is
 * Application.UpdateAll();
 */
Application::Application()
{

}

/**
 * @brief 
 * Sets up the entire application.
 * This needs to be called in void setup.
 * @return true:
 * Successfully created the application.
 * @return false:
 * Failed to create the application.
 */
bool Application::Setup()
{
    controllerA = new Controller(
        PIN_CONTROLLER_A_DETECTION,
        PIN_CONTROLLER_A_TOP_BUTTON,
        PIN_CONTROLLER_A_R_BUTTON,
        PIN_CONTROLLER_A_L_BUTTON,
        PIN_CONTROLLER_A_BOT_BUTTON,
        PIN_CONTROLLER_A_JOY_BUTTON,
        PIN_CONTROLLER_A_JOY_X,
        PIN_CONTROLLER_A_JOY_Y,
        PIN_CONTROLLER_A_ACCELEROMETER_X,
        PIN_CONTROLLER_A_ACCELEROMETER_Y,
        PIN_CONTROLLER_A_ACCELEROMETER_Z,
        PIN_CONTROLLER_A_HEARTHBEAT,
        PIN_CONTROLLER_A_BARGRAPH_A,
        PIN_CONTROLLER_A_BARGRAPH_B,
        PIN_CONTROLLER_A_BARGRAPH_C,
        PIN_CONTROLLER_A_BARGRAPH_D,
        PIN_CONTROLLER_A_BARGRAPH_E,
        PIN_CONTROLLER_A_BARGRAPH_F,
        PIN_CONTROLLER_A_BARGRAPH_G,
        PIN_CONTROLLER_A_BARGRAPH_H,
        PIN_CONTROLLER_A_BARGRAPH_I,
        PIN_CONTROLLER_A_BARGRAPH_J,
        0
    );

    controllerB = new Controller(
        PIN_CONTROLLER_B_DETECTION,
        PIN_CONTROLLER_B_TOP_BUTTON,
        PIN_CONTROLLER_B_R_BUTTON,
        PIN_CONTROLLER_B_L_BUTTON,
        PIN_CONTROLLER_B_BOT_BUTTON,
        PIN_CONTROLLER_B_JOY_BUTTON,
        PIN_CONTROLLER_B_JOY_X,
        PIN_CONTROLLER_B_JOY_Y,
        PIN_CONTROLLER_B_ACCELEROMETER_X,
        PIN_CONTROLLER_B_ACCELEROMETER_Y,
        PIN_CONTROLLER_B_ACCELEROMETER_Z,
        PIN_CONTROLLER_B_HEARTHBEAT,
        PIN_CONTROLLER_B_BARGRAPH_A,
        PIN_CONTROLLER_B_BARGRAPH_B,
        PIN_CONTROLLER_B_BARGRAPH_C,
        PIN_CONTROLLER_B_BARGRAPH_D,
        PIN_CONTROLLER_B_BARGRAPH_E,
        PIN_CONTROLLER_B_BARGRAPH_F,
        PIN_CONTROLLER_B_BARGRAPH_G,
        PIN_CONTROLLER_B_BARGRAPH_H,
        PIN_CONTROLLER_B_BARGRAPH_I,
        PIN_CONTROLLER_B_BARGRAPH_J,
        1
    );

    muonDetector = new MuonDetector(PIN_MUON);

    lcd.begin(16, 2);

    communication.StartSerial(115200);
    communication.LinkControllers(controllerA, controllerB);
    communication.LinkMuonDetector(muonDetector);
    return true;
}

/**
 * @brief 
 * Resets everything to OFF.
 * @return true:
 * Successfully reset to its default state
 * @return false:
 * Faild to set to a reset state.
 */
bool Application::Reset()
{
    controllerA->Reset();
    controllerB->Reset();
    muonDetector->ResetCount();
    lcd.clear();
    return true;
}

/**
 * @brief 
 * Updates the Application object.
 * Updates all the objects within controllers and LCDS
 * @return true:
 * Successfully updated all the aspects of the application
 * @return false:
 * Failed to update all the aspects of the application
 */
bool Application::UpdateAll()
{
    if(millis()%1000 == 0)
    {
        controllerA->GetBarGraph()->FlipAll();
    }

    controllerA->Update();
    controllerB->Update();
    muonDetector->Update();
    communication.Update();
    return true;
}

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
bool Application::UpdateLCD()
{
    lcd.setCursor(0, 0);
    lcd.print("amogus          ");
    return true;
}

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
bool Application::AnswerCommunicationProtocol()
{
    return false;
}

/**
 * @brief Get the Time Since Last Communication.
 * Is reset by @ref AnswerCommunicationProtocol.
 * Allows the Application to know if its
 * disconnected from the PC and display a message
 * on the LCD if thats the case.
 * @return int
 * Time in milliseconds
 */
int Application::GetTimeSinceLastCommunication()
{
    return 0;
}
