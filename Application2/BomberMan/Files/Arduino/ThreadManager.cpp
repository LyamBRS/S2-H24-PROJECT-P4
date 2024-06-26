/**
 * @file ThreadManager.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-02-26
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "ThreadManager.hpp"

// - PROGRAM - //

/**
 * @brief 
 * Function executed in another thread
 */
void ArduinoThreadManager::threadFunction(int newValue)
{
    while(shouldExecute)
    {
        shouldExecute = false;
        try{
            threadValues++;
            while(delayBetweenMessageTimer.TimeLeft() != 0)
            {
                threadValues++;
                switch(wantedFunction)
                {
                    case(Functions::endComPort):
                        canReadArduino = false;
                        wantedFunction = Functions::nothing;
                        if(arduinoObject.Disconnect() == false)
                        {
                            executionResult = -1;
                        }
                        canReadArduino = true;
                        executionResult = 1;
                        break;
    
                    case(Functions::startComPort):
                        canReadArduino = false;
                        wantedFunction = Functions::nothing;
                        if(arduinoObject.Connect() == false)
                        {
                            executionResult = -1;
                        }
                        executionResult = 1;
                        canReadArduino = true;
                        break;
    
                    case(Functions::reset):
                        wantedFunction = Functions::nothing;
                        executionResult = -1;
                        break;
                }
            }
            canReadArduino = false;
            arduinoObject.Update();
            threadValues++;
            canReadArduino = true;
        }
        catch(...)
        {
            std::cout << std::endl << "THREAD: ERROR" << std::endl;
        }
    }
    //std::cout << std::endl << "THREAD: FATAL WHILE ERROR" << std::endl;
}

/**
 * @brief
 * Tells you how well the function you wanted executed, executed.
 * -1: "False / error"
 * 0: No result yet
 * 1: Success!
 * @return int 
 */
int ArduinoThreadManager::GetFunctionExecutionResult()
{
    return executionResult;
}

bool ArduinoThreadManager::SetExecutionFunction(unsigned char newExecutionFunction)
{
    waitForExecutionTimer.Reset();
    executionResult = 0;
    wantedFunction = newExecutionFunction;
    return true;
}



/**
 * @brief 
 * Waits 2 seconds max until the queued function is
 * successfully executed or not.
 * @return true
 * A new execution result is available.
 * @return false:
 * Failed to get new execution result.
 */
bool ArduinoThreadManager::WaitTillFunctionExecuted()
{
    waitForExecutionTimer.Reset();

    while(GetFunctionExecutionResult() == 0)
    {
        if(waitForExecutionTimer.TimeLeft()==0)
        {
            return false;
        }
    }
    return true;
}

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
bool ArduinoThreadManager::FunctionShouldBeExecuted()
{
    uint64_t timeLeft = waitForExecutionTimer.TimeLeft();

    if(timeLeft==0)
    {
        return true;
    }

    if(GetFunctionExecutionResult() == 0)
    {
        return false;
    }
    return true;
}

bool ArduinoThreadManager::GetThreadStatus()
{
    //std::cout << threadValues << " " << oldThreadValues << std::endl;
    static int wasNotAnsweringCounter = 0;

    if(threadValues == oldThreadValues)
    {
        wasNotAnsweringCounter++;
        if(wasNotAnsweringCounter>100)
        {
            return false;
        }
        return true;
    }
    oldThreadValues = threadValues;
    wasNotAnsweringCounter = 0;
    return true;
}

/**
 * @brief Get the Arduino object
 * used in the thread.
 * @return Arduino 
 */
Arduino* ArduinoThreadManager::GetArduino()
{
    if(!canReadArduino)
    {
        return &fakeArduinoObject;
    }
    return &arduinoObject;
}