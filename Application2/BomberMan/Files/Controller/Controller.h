/**
 * @file Controller.h
 * @author LyamBRS
 * @brief 
 * Header definition of the attribute class
 * @ref Controller. That class is used to hold
 * values returned by the Arduino for a specific
 * controller and can be used to translate these
 * various input controls into actual, application
 * inputs.
 * @version 0.1
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //

// - DEFINES - //

// - CLASS - //

/**
 * @brief 
 * Simple attribute holding class that is used to
 * store the last values received during a communication
 * with the Arduino. These values directly corresponds
 * to the ones on the Arduino card. You will need
 * to manually set these members when a communication
 * from the Arduino is received.
 * 
 * All values defaults to off or 0 by default.
 */
class Controller
{
    private:

    public:

        /**
         * @brief 
         * Value rangine from 0 to 100% corresponding to the
         * current value of the X axis of that controller's
         * joystick. At 50%, the joystick is resting.
         */
        int joystickX = 0;

        /**
         * @brief 
         * Value rangine from 0 to 100% corresponding to the
         * current value of the Y axis of that controller's
         * joystick. At 50%, the joystick is resting.
         */
        int joystickY = 0;

        /**
         * @brief 
         * Represents the current state of the joystick's
         * button present on that controller.
         * If true, the button is pressed.
         */
        bool joystickButton = false;

        /**
         * @brief 
         * Represents the current state of the top most
         * button present on that controller. If true, 
         * the button is pressed.
         */     
        bool topButton = false;

        /**
         * @brief 
         * Represents the current state of the bottom most
         * button present on that controller. If true, 
         * the button is pressed.
         */  
        bool bottomButton = false;

        /**
         * @brief 
         * Represents the current state of the left most
         * button present on that controller. If true, 
         * the button is pressed.
         */  
        bool leftButton = false;

        /**
         * @brief 
         * Represents the current state of the right most
         * button present on that controller. If true, 
         * the button is pressed.
         */  
        bool rightButton = false;

        /**
         * @brief 
         * Represents a 10 bits number that corresponds
         * to individual LED states on the controller's
         * bar graph. If 0, they are all off.
         */  
        int SentBarGraphBits = 0;
        int ReceivedBarGraphBits = 0;

        /**
         * @brief 
         * Represents the value of the accelerometer's X
         * axis. Value ranges from 0 to 100%
         */
        int accelerometerX = 0;

        /**
         * @brief 
         * Represents the value of the accelerometer's Y
         * axis. Value ranges from 0 to 100%
         */
        int accelerometerY = 0;

        /**
         * @brief 
         * Represents the value of the accelerometer's Z
         * axis. Value ranges from 0 to 100%
         */
        int accelerometerZ = 0;

        /**
         * @brief 
         * Tells you if that controller is currently
         * connected to the arduino or not.
         * If true, that controller is currently connected.
         */
        bool isConnected = false;

        /**
         * @brief Construct a new Controller object.
         * Sets all the values of that controller to
         * 0 or off by default. You will need to
         * manually put the values into this class
         * when a communication is received from the
         * arduino.
         */
        Controller();

        /**
         * @brief
         * Puts all the values of the controller class
         * back to their default values.
         * @attention
         * THIS NEEDS TO BE CALLED IF THE CONTROLLER
         * IS NO LONGER SEEN ONLINE OR IF THE
         * COMMUNICATION WITH THE ARDUINO IS LOST.
         */
        bool Reset();

        int controllerID = 0;
};

// - FUNCTIONS - //
