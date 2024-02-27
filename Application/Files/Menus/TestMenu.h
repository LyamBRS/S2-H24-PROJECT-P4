/**
 * @file TestMenu.h
 * @author LyamBRS
 * @brief
 * Header definition of the TestMenu class
 * which allows a TestMenu to be handled.
 * @version 0.1
 * @date 2024-02-15
 * @copyright Copyright (c) 2024
 */
#pragma once

// - INCLUDES - //
#include "../Application/AppHandler.h"
#include "../Colour/Colour.h"
#include "Menu.h"

// - DEFINES - //
#define APP_NO_ARDUINO 0
#define APP_MAIN 1
#define APP_LCD 2
#define APP_BARGRAPH 3
#define APP_RECEIVED_MESSAGE 4
#define APP_CONTROLLER 5

#define LCD_NO_ERROR 0
#define LCD_REMOVED_A_LETTER 1
#define LCD_ADDED_A_LETTER 2
#define LCD_ALREADY_EMPTY 3
#define LCD_MESSAGE_TOO_LONG 4
#define LCD_MESSAGE_MUST_BE_20_LONG 5
#define LCD_INCORRECT_KEYBOARD 6
#define LCD_MESSAGE_UPDATED 7

#define APP_MAX_SUBMENU 5
#define APP_MIN_SUBMENU 0

// - CLASS - //
//class Application;

class TestMenu : public Menu
{
    private:
        bool DrawNoArduinoMenu();
        bool DrawMainTestMenu();
        bool DrawLCDTestMenu();
        bool DrawBarGraphTestMenu();
        bool DrawReceivedMessageMenuKeyboard();
        bool DrawControllerMenu();

        bool HandleNoArduinoMenu(int keyBoardKey);
        bool HandleMainTestMenuKeyboard(int keyBoardKey);
        bool HandleLCDTestMenuKeyboard(int keyBoardKey);
        bool HandleBarGraphTestMenuKeyboard(int keyBoardKey);
        bool HandleReceivedMessageMenuKeyboard(int keyBoardKey);
        bool HandleControllerMenuKeyboard(int keyBoardKey);

        int selectedSubMenu = 0;
        int wantedBitsPlayerA = 0;
        int wantedBitsPlayerB = 0;
        std::string newLCDMessage = "";
        std::string bargraphMessage = "";
    public:
        TestMenu(AppHandler* currentAppHandler);
        bool HandleKeyboard(int keyBoardKey);
        bool Draw();
        bool OnEnter();
        bool OnExit();
        bool Update();
};