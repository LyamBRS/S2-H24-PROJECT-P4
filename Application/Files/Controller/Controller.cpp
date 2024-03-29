/**
 * @file Controller.cpp
 * @author LyamBRS
 * @brief
 * Program file for the attribute class
 * @ref Controller. That class is used to hold
 * values returned by the Arduino for a specific
 * controller and can be used to translate these
 * various input controls into actual, application
 * inputs.
 * @version 0.1
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */

 // - INCLUDES - //
#include "../Controller/Controller.h"

 // - LOCALS - //
Controller keyboardLeft;
Controller keyboardRight;

 // - CLASS - //

/**
 * @brief Construct a new Controller object.
 * Sets all the values of that controller to
 * 0 or off by default. You will need to
 * manually put the values into this class
 * when a communication is received from the
 * arduino.
 */
Controller::Controller()
{
    joystickX = 0;
    joystickY = 0;
    joystickButton = false;
    topButton = false;
    bottomButton = false;
    leftButton = false;
    rightButton = false;
    SentBarGraphBits = 0;
    ReceivedBarGraphBits = 0;
    accelerometerX = 0;
    accelerometerY = 0;
    accelerometerZ = 0;
    isConnected = false;
}

/**
 * @brief
 * Puts all the values of the controller class
 * back to their default values.
 * @attention
 * THIS NEEDS TO BE CALLED IF THE CONTROLLER
 * IS NO LONGER SEEN ONLINE OR IF THE
 * COMMUNICATION WITH THE ARDUINO IS LOST.
 */
bool Controller::Reset()
{
    joystickX = 0;
    joystickY = 0;
    joystickButton = false;
    topButton = false;
    bottomButton = false;
    leftButton = false;
    rightButton = false;
    SentBarGraphBits = 0;
    ReceivedBarGraphBits = 0;
    accelerometerX = 0;
    accelerometerY = 0;
    accelerometerZ = 0;
    isConnected = false;
	return false;
}

