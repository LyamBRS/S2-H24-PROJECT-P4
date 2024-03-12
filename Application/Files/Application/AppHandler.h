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

        SimpleTimer frameTimer = SimpleTimer(10);

        int wantedSelectedMenu = 1;
        int currentSelectedMenu = 0;

        int selection = 0;

        /**
         * @brief 
         * # wantedMapIndex
         * @brief
         * Global variable allowing any @ref Menu to
         * specify a wanted @ref Map index to use in
         * the @ref Game which will be created when
         * the @ref OnEnter method of @ref GameMenu
         * is called, which is whenever a valid map is
         * selected.
         * @brief
         * That index is then verified and used to gather
         * the JSON of the required map directly inside
         * of @ref GameMenu
         * @attention
         * Defaults to 0. May be a potential problem if
         * your selected maps is always the first one
         * regardless of the actually displayed selected
         * map.
         */
        int wantedMapIndex = 0;

        int oldAmountOfComPorts = 0;

        bool requiresNewDrawing = true;
};