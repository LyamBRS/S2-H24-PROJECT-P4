/**
 * @file Controller.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-02-27
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "Controller.h"

// - PROGRAM - //

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
Controller::Controller(int detectionPin, 
                    int topButtonPin, 
                    int rightButtonPin,
                    int leftButtonPin, 
                    int bottomButtonPin, 
                    uint8_t joystickButtonPin, 
                    uint8_t joystickXAxisPin, 
                    uint8_t joystickYAxisPin, 
                    uint8_t accelerometerXAxisPin, 
                    uint8_t accelerometerYAxisPin, 
                    uint8_t accelerometerZAxisPin, 
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
                    int barGraphJPin,
                    int ID)
{
    detection = new Button(detectionPin, false, 0);
    hearthbeat = new LED(hearthBeatPin);
    topButton = new Button(topButtonPin);
    bottomButton = new Button(bottomButtonPin);
    leftButton = new Button(leftButtonPin);
    rightButton = new Button(rightButtonPin);
    joystick = new Joystick(joystickButtonPin, joystickXAxisPin, joystickYAxisPin);
    accelerometer = new Accelerometer(accelerometerXAxisPin, accelerometerYAxisPin, accelerometerZAxisPin);
    barGraph = new BarGraph(                    
        barGraphAPin, 
        barGraphBPin,
        barGraphCPin,
        barGraphDPin, 
        barGraphEPin,
        barGraphFPin,
        barGraphGPin, 
        barGraphHPin,
        barGraphIPin,
        barGraphJPin
    );
    canBeUsed = true;
}

/**
 * @brief 
 * Resets everything to OFF.
 * @return true:
 * Successfully reset the controller to its default state
 * @return false:
 * Faild to set the controller to a reset state.
 */
bool Controller::Reset()
{
    if(!canBeUsed) return false;
    hearthbeatTimer.Reset();
    barGraph->TurnAllOff();
    hearthbeat->TurnOff();
    joystick->Reset();
    accelerometer->Reset();
    topButton->Reset();
    bottomButton->Reset();
    leftButton->Reset();
    rightButton->Reset();
    return true;
}

/**
 * @brief Get the Bar Graph object.
 * Returns a pointer to the bar graph
 * that is on this Controller so that
 * you can do whatver you want to it.
 * @return BarGraph* 
 */
BarGraph* Controller::GetBarGraph()
{
    return barGraph;
}

/**
 * @brief Get the Accelerometer object.
 * Returns a pointer to the accelerometer
 * that is on this Controller so that
 * you can do whatver you want to it.
 * @return Accelerometer* 
 */
Accelerometer* Controller::GetAccelerometer()
{
    return accelerometer;
}
        
/**
 * @brief Get the Button object.
 * Returns a pointer to the top button
 * object that is on this Controller so that
 * you can do whatver you want to it.
 * @return Button* 
 */
Button* Controller::GetTopButton()
{
    return topButton;
}

/**
 * @brief Get the Button object.
 * Returns a pointer to the left button
 * object that is on this Controller so that
 * you can do whatver you want to it.
 * @return Button* 
 */
Button* Controller::GetLeftButton()
{
    return leftButton;
}

/**
 * @brief Get the Button object.
 * Returns a pointer to the right button
 * object that is on this Controller so that
 * you can do whatver you want to it.
 * @return Button* 
 */
Button* Controller::GetRightButton()
{
    return rightButton;
}

/**
 * @brief Get the Button object.
 * Returns a pointer to the bpttom button
 * object that is on this Controller so that
 * you can do whatver you want to it.
 * @return Button* 
 */
Button* Controller::GetBottomButton()
{
    return bottomButton;
}

/**
 * @brief Get the Joystick object.
 * Returns a pointer to the joystick
 * object that is on this Controller so that
 * you can do whatver you want to it.
 * @return Button* 
 */
Joystick* Controller::GetJoystick()
{
    return joystick;
}

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
bool Controller::SetGraphDisplay(int bits)
{
    if(!canBeUsed) return false;
    barGraph->SetBits(bits);
    return true;
}

/**
 * @brief
 * Returns if the card is connected or
 * not.
 * @return true:
 * The card is currently connected.
 * @return false:
 * The card is not currently connected.
 */
bool Controller::GetDetection()
{
    if(!canBeUsed) return false;
    return detection->GetState();
}

/**
 * @brief 
 * Updates the Controller object.
 * Updates all the objects within the controller.
 * @return true:
 * Successfully updated the Controller
 * @return false:
 * Failed to update the Controller
 */
bool Controller::Update()
{
    if(!canBeUsed) return false;
    if(hearthbeatTimer.TimeLeft() == 0)
    {
        hearthbeat->FlipState();
    }

    if(!barGraph->Update())
    {
        Serial1.println("Controller.cpp.261");
    }

    if(!accelerometer->Update())
    {
        Serial1.println("Controller.cpp.266");
    }

    if(!joystick->Update())
    {
        Serial1.println("Controller.cpp.271");
    }

    if(!hearthbeat->Update())
    {
        Serial1.println("Controller.cpp.276");
    }

    if(!topButton->Update())
    {
        //Serial1.println("Controller.cpp.281");
    }

    detection->Update();
    leftButton->Update();
    rightButton->Update();
    bottomButton->Update();

    return true;
}