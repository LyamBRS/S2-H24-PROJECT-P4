/**
 * @file ThreadManager.hpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-02-26
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include <iostream>
#include <thread>
#include <mutex>
#include "Arduino.h"
#include "../SimpleTimer/SimpleTimer.h"

// - A LITTLE TROLLLING - //
enum Functions {
    nothing = 0,
    startComPort = 1,
    endComPort = 2,
    reset = 3
};

class ArduinoThreadManager {
private:
    Arduino arduinoObject;
    Arduino fakeArduinoObject;
    std::thread myThread;
    unsigned char wantedFunction = Functions::nothing;
    SimpleTimer waitForExecutionTimer = SimpleTimer(5000);
    SimpleTimer delayBetweenMessageTimer = SimpleTimer(10);
    int executionResult = 0;
    int threadValues = 0;
    int oldThreadValues = 0;
    bool shouldExecute = true;
    bool canReadArduino = true;

public:
    ArduinoThreadManager()
    {

    } //: myThread(&ArduinoThreadManager::threadFunction, this, 42) {}

    ~ArduinoThreadManager() {
        shouldExecute = false;
        // Make sure to join the thread in the destructor
        //if (myThread.joinable()) {
        //    myThread.join();
        //}
    }

    /**
     * @brief 
     * Function executed in another thread
     */
    void threadFunction(int newValue);

    /**
     * @brief
     * Tells you how well the function you wanted executed, executed.
     * -1: "False / error"
     * 0: No result yet
     * 1: Success!
     * @return int 
     */
    int GetFunctionExecutionResult();

    /**
     * @brief 
     * Waits 2 seconds max until the queued function is
     * successfully executed or not.
     * @return true
     * A new execution result is available.
     * @return false:
     * Failed to get new execution result.
     */
    bool WaitTillFunctionExecuted();

    /**
     * @brief 
     * Tells you if the function should be executed or not.
     * It is a spinoff of @ref WaitTillFunctionExecuted
     * which doesnt block the program.
     * @return true:
     * timeout happenned / function has executed
     * @return false:
     * Still waiting on the function to be executed.
     */
    bool FunctionShouldBeExecuted();

    bool SetExecutionFunction(unsigned char newExecutionFunction);

    bool GetThreadStatus();

    /**
     * @brief Get the Arduino object
     * used in the thread.
     * @return Arduino 
     */
    Arduino* GetArduino();
};