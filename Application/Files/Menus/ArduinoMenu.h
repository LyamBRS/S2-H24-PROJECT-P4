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
// - INCLUDES - //
#include "Menu.h"
#include "../Application/Application.h"

// - DEFINES - //

// - CLASS - //

class ArduinoMenu : public Menu
{
    private:
        bool DrawArduinoMainMenu();
        bool DrawBaudrateSelectionMenu();
        bool DrawComPortSelectionMenu();
        bool DrawConnectMenu();
        bool DrawDisconnectMenu();

        bool HandleKeyboardMainMenu();
        bool HandleKeyboardBaudrateMenu();
        bool HandleKeyboardComPortMenu();
        bool HandleKeyboardConnectMenu();
        bool HandleKeyboardDisconnectMenu();

        int selectedSubMenu = 0;

    public: 
        bool HandleKeyboard(int keyBoardKey);
        bool Draw();
        bool OnEnter();
        bool OnExit();
}