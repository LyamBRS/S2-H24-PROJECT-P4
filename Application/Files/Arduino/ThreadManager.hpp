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

// - A LITTLE TROLLLING - //

/**
 * @brief 
 * # ArduinoThreadManager
 * @brief
 * This class is used to pass information
 * to the @ref Arduino class. NEVER use
 * the arduino class WITHOUT this class
 * as there can be read/write conflicts
 * otherwise.
 * This class is used to have an arduino class
 * that is completely seperated from the main
 * thread of the application. We multi tasking
 * in here fr.
 */
class ArduinoThreadManager
{
    private:
        bool writeFlag = true;
        Arduino arduino;
    public:
        /**
         * @brief 
         * # ArduinoThreadManager
         * @brief
         * This class is used to pass information
         * to the @ref Arduino class. NEVER use
         * the arduino class WITHOUT this class
         * as there can be read/write conflicts
         * otherwise.
         * This class is used to have an arduino class
         * that is completely seperated from the main
         * thread of the application. We multi tasking
         * in here fr.
         */    
        ArduinoThreadManager();

        /**
         * @brief 
         * # CanWrite
         * @brief
         * Tells you if you can write in the class at any
         * given time.
         * @attention
         * ### ONLY WRITE IN THE CLASS WHEN THIS IS TRUE.
         * @return true:
         * You can safely write in the class
         * @return false:
         * You cannot write in the class at the moment.
         */
        bool CanWrite();

        /**
         * @brief 
         * # BeginWrite
         * @brief
         * MUST be called when you are modifying values of the
         * private arduino class of this objet.
         * @return true:
         * You can write into @ref Controller classes safely
         * @return false:
         * You cannot currently write data in the arduino class
         */
        bool BeginWrite();

        /**
         * @brief 
         * # EndWrite
         * @brief
         * @return true:
         * You successfully ended your writing period
         * @return false:
         * You failed to end your writing period.
         */
        bool EndWrite();

        /**
         * @brief 
         * # CueFunctionForExecution
         * @brief
         * @param functionID
         * The function that needs to be executed next.
         * @return true:
         * Successfully set that as the next function to be executed.
         * @return false:
         * Failed to set the specified number as the next function to be executed.
         */
        bool CueFunctionForExecution(unsigned char functionID);

        void ThreadFunction();
};