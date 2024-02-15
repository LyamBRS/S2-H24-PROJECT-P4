/**
 * @file Controller.h
 * @author LyamBRS
 * @brief 
 * Contains the header definition of the
 * Controller class. You know... the class
 * that makes up a controller? The funny
 * PCB we designed? yeah that thing.
 * @version 0.1
 * @date 2024-02-11
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include "Button.h"
#include "LED.h"
#include "Joystick.h"
#include "BarGraph.h"
#include "Accelerometer.h"

// - DEFINES - //

// - CLASS - //

/**
 * @brief 
 * Class used to create a Controller objects.
 * A controller consists of 1 accelerometer,
 * 1 joystick, 4 buttons, 1 LED and 1 bar graph
 */
class Controller 
{
    private:
        Button topButton;
        Button bottomButton;
        Button leftButton;
        Button rightButton;
        Accelerometer accelerometer;
        Joystick joystick;
        BarGraph barGraph;

        bool isConnected = false;

    public:

        /**
         * @brief
         * Builds a new controller based on the pins
         * given.
         * @param detectionPin
         * The arduino pin used to detect if the controller is currently
         * plugged in or not.
         * @param topButtonPin
         * The arduino pin that reads the top button of that controller.
         * @param rightButtonPin
         * The arduino pin that reads the top button of that controller.
         * @param leftButtonPin
         * The arduino pin that reads the left button of that controller.
         * @param bottomButtonPin 
         * The arduino pin that reads the bottom button of that controller.
         * @param joystickButtonPin
         * The arduino pin that reads the digital joystick button of that controller.
         * @param joystickXAxisPin
         * The arduino pin that reads the analog joystick Y axis of that controller.
         * @param joystickYAxisPin 
         * The arduino pin that reads the analog joystick X axis of that controller.
         * @param accelerometerXAxisPin
         * The arduino pin that reads the analog accelerometer 3V3 X axis of that controller.
         * @param accelerometerYAxisPin
         * The arduino pin that reads the analog accelerometer 3V3 Y axis of that controller.
         * @param accelerometerZAxisPin
         * The arduino pin that reads the analog accelerometer 3V3 Z axis of that controller.
         * @param hearthBeatPin
         * The arduino pin that sets the hearthbeat LED state
         * @param barGraphAPin
         * The arduino pin that sets the LED A of the controller's bar graph.
         * @param barGraphBPin
         * The arduino pin that sets the LED B of the controller's bar graph.
         * @param barGraphCPin 
         * The arduino pin that sets the LED C of the controller's bar graph.
         * @param barGraphDPin
         * The arduino pin that sets the LED D of the controller's bar graph.
         * @param barGraphEPin
         * The arduino pin that sets the LED E of the controller's bar graph.
         * @param barGraphFPin
         * The arduino pin that sets the LED F of the controller's bar graph.
         * @param barGraphGPin
         * The arduino pin that sets the LED G of the controller's bar graph.
         * @param barGraphHPin 
         * The arduino pin that sets the LED H of the controller's bar graph.
         * @param barGraphIPin
         * The arduino pin that sets the LED I of the controller's bar graph.
         * @param barGraphJPin
         * The arduino pin that sets the LED J of the controller's bar graph.
         */
        Controller(int detectionPin, 
                    int topButtonPin, 
                    int rightButtonPin,
                    int leftButtonPin, 
                    int bottomButtonPin, 
                    int joystickButtonPin, 
                    int joystickXAxisPin, 
                    int joystickYAxisPin, 
                    int accelerometerXAxisPin, 
                    int accelerometerYAxisPin, 
                    int accelerometerZAxisPin, 
                    int hearthBeatPin, 
                    int barGraphAPin, 
                    int barGraphBPin,
                    int barGraphCPin,
                    int barGraphDPin, 
                    int barGraphEPin,
                    int barGraphFPin,
                    int barGraphGPin, 
                    int barGraphHPin,
                    int barGraphIPin,
                    int ID
                    );

        /**
         * @brief 
         * Resets everything to OFF.
         * @return true:
         * Successfully reset the controller to its default state
         * @return false:
         * Faild to set the controller to a reset state.
         */
        bool Reset();

        /**
         * @brief Get the Bar Graph object.
         * Returns a pointer to the bar graph
         * that is on this Controller so that
         * you can do whatver you want to it.
         * @return BarGraph* 
         */
        BarGraph* GetBarGraph();

        /**
         * @brief Get the Accelerometer object.
         * Returns a pointer to the accelerometer
         * that is on this Controller so that
         * you can do whatver you want to it.
         * @return Accelerometer* 
         */
        Accelerometer* GetAccelerometer();
        
        /**
         * @brief Get the Button object.
         * Returns a pointer to the top button
         * object that is on this Controller so that
         * you can do whatver you want to it.
         * @return Button* 
         */
        Button* GetTopButton();

        /**
         * @brief Get the Button object.
         * Returns a pointer to the left button
         * object that is on this Controller so that
         * you can do whatver you want to it.
         * @return Button* 
         */
        Button* GetLeftButton();

        /**
         * @brief Get the Button object.
         * Returns a pointer to the right button
         * object that is on this Controller so that
         * you can do whatver you want to it.
         * @return Button* 
         */
        Button* GetRightButton();

        /**
         * @brief Get the Button object.
         * Returns a pointer to the bpttom button
         * object that is on this Controller so that
         * you can do whatver you want to it.
         * @return Button* 
         */
        Button* GetBottomButton();

        /**
         * @brief Get the Joystick object.
         * Returns a pointer to the joystick
         * object that is on this Controller so that
         * you can do whatver you want to it.
         * @return Button* 
         */
        Joystick* GetJoystick();

        /**
         * @brief
         * Sets a 10 bit value to be displayed
         * as LEDs on the controller.
         * @param bits
         * Value ranging from 0 to 65472
         * @return true:
         * Successfully updated the bar graph
         * with the specified bits
         * @return false:
         * Failed to update the bar graph with
         * the specified bits.
         */
        bool SetGraphDisplay(int bits);

        /**
         * @brief
         * Returns if the card is connected or
         * not.
         * @return true:
         * The card is currently connected.
         * @return false:
         * The card is not currently connected.
         */
        bool GetDetection();

        /**
         * @brief 
         * Updates the Controller object.
         * Updates all the objects within the controller.
         * @return true:
         * Successfully updated the Controller
         * @return false:
         * Failed to update the Controller
         */
        bool Update();
};
