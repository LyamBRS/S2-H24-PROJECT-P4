/**
 * @file ArduinoMenu.h
 * @author LyamBRS
 * @brief
 * Header file containing the menu
 * definition for the Arduino setup.
 * @version 0.1
 * @date 2024-02-15
 * @copyright Copyright (c) 2024
 */
#pragma once

// - INCLUDES - //
#include "../Application/AppHandler.h"
#include "Menu.h"
#include "../Serial/PortDetector.h"

// - DEFINES - //
#define APP_MAIN_MENU 0
#define APP_BAUD_RATE_MENU 1
#define APP_COM_PORT_MENU 2
#define APP_CONNECTING_MENU 3
#define APP_DISCONNECTING_MENU 4

// - CLASS - //
class ArduinoMenu : public Menu
{
    private:
        bool DrawArduinoMainMenu();
        bool DrawBaudrateSelectionMenu();

        /**
         * @brief 
        * Draws the menu that allows the user to select
        * a wanted com port as well as a wanted baud rate
        * and see if their connection was successful or not.
        * @return true 
        * @return false 
        */
        bool DrawComPortSelectionMenu();
        bool DrawConnectMenu();
        bool DrawDisconnectMenu();

        bool HandleKeyboardMainMenu(int keyBoardKey);
        bool HandleKeyboardBaudrateMenu(int keyBoardKey);
        bool HandleKeyboardComPortMenu(int keyBoardKey);
        bool HandleKeyboardConnectMenu(int keyBoardKey);
        bool HandleKeyboardDisconnectMenu(int keyBoardKey);

        int selectedSubMenu = 0;

    public:
        ArduinoMenu(AppHandler* currentAppHandler);
        bool HandleKeyboard(int keyBoardKey);
        bool Update();
        bool Draw();
        bool OnEnter();
        bool OnExit();
};