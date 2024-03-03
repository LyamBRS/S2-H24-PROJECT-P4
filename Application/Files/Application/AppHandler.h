/**
 * @file AppHandler.h
 * @author LyamBRS
 * @brief 
 * Header definition of the AppHandler class which
 * was created after a long and painful battle with
 * circular include problems and private member
 * bullshit. This allows menus to handle and change
 * attributes of the application without directly
 * accessing the actual application.
 * Its an interface basically.
 * @version 0.1
 * @date 2024-02-15
 * @copyright Copyright (c) 2024
 */
#pragma once

// - INCLUDES - //
#include "../Arduino/Arduino.h"
#include "../SimpleTimer/SimpleTimer.h"
#include "../Game/Game.h"
#include "../Arduino/ThreadManager.hpp"

// - DEFINES - //

// - CLASS - //
/**
 * @brief
 * # AppHandler
 * @brief
 * the AppHandler class which
 * was created after a long and painful battle with
 * circular include problems and private member
 * bullshit.
 * This allows menus to handle and change
 * attributes of the application without directly
 * accessing the actual application.
 * Its an interface basically.
 */
class AppHandler
{
    public:
        AppHandler();

        ArduinoThreadManager arduinoThread;
        Game currentGame;

        SimpleTimer frameTimer = SimpleTimer(10);

        int wantedSelectedMenu = 1;
        int currentSelectedMenu = 0;

        int selection = 0;

        int oldAmountOfComPorts = 0;

        bool requiresNewDrawing = true;
};