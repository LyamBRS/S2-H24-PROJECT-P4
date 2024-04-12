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
#include "../Controller/Controller.h"
#include "../Colour/Colour.h"


#include <Windows.h>
#include <functional>
#include <iostream>

#include <QObject>

// - DEFINES - //
#define CONTROLLER_TYPE_ARDUINO_A 1
#define CONTROLLER_TYPE_ARDUINO_B 2
#define CONTROLLER_TYPE_KEYBOARD_A 3
#define CONTROLLER_TYPE_KEYBOARD_B 4
#define CONTROLLER_TYPE_BRS_GAMEPAD 5
#define CONTROLLER_TYPE_AMOUNT 5

#define CONTROLLER_KEYBOARD_A_Y_T 'W'
#define CONTROLLER_KEYBOARD_A_Y_B 'S'
#define CONTROLLER_KEYBOARD_A_X_L 'A'
#define CONTROLLER_KEYBOARD_A_X_R 'D'
#define CONTROLLER_KEYBOARD_A_LEFT 'Z'
#define CONTROLLER_KEYBOARD_A_RIGHT 'C'
#define CONTROLLER_KEYBOARD_A_UP 'X'
#define CONTROLLER_KEYBOARD_A_DOWN 'E'
#define CONTROLLER_KEYBOARD_A_SELECT 'Q'

#define CONTROLLER_KEYBOARD_B_Y_T VK_NUMPAD5
#define CONTROLLER_KEYBOARD_B_Y_B VK_NUMPAD2
#define CONTROLLER_KEYBOARD_B_X_L VK_NUMPAD1
#define CONTROLLER_KEYBOARD_B_X_R VK_NUMPAD3
#define CONTROLLER_KEYBOARD_B_LEFT  VK_NUMPAD7
#define CONTROLLER_KEYBOARD_B_RIGHT VK_NUMPAD9
#define CONTROLLER_KEYBOARD_B_UP    VK_DIVIDE
#define CONTROLLER_KEYBOARD_B_DOWN  VK_NUMPAD8
#define CONTROLLER_KEYBOARD_B_SELECT VK_MULTIPLY

// - ENUM - //
enum QMenus
{
    MainMenu,
    MapSelection,
    PlayerJoining,
    Countdown,
    Game,
    PlayingGame,
    PauseMenu,
    ExitMenu,
    Formulaire,
    Settings,
    Disconnect,
    Error
};

// - CLASS - //

class BomberManGame;

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
class AppHandler : public QObject
{

    public:
        typedef std::function<void(int)> QMenuChangerFunction;
        QMenuChangerFunction QSetMenu;
        AppHandler(QMenuChangerFunction QmenuChangeFunction);
        AppHandler();

        ArduinoThreadManager arduinoThread;

        SimpleTimer frameTimer = SimpleTimer(10);

        Controller letterKeyboard;
        Controller numpadKeyboard;

        int wantedSelectedMenu = 1;
        int currentSelectedMenu = 0;

        int selection = 0;

        bool redrawOnKeyboardHits = true;

        /**
         * @brief 
         * # wantedMapIndex
         * @brief
         * Global variable allowing any @ref Menu to
         * specify a wanted @ref Map index to use in
         * the @ref BomberManGame which will be created when
         * the @ref OnEnter method of @ref cGameMenu
         * is called, which is whenever a valid map is
         * selected.
         * @brief
         * That index is then verified and used to gather
         * the JSON of the required map directly inside
         * of @ref cGameMenu
         * @attention
         * Defaults to 0. May be a potential problem if
         * your selected maps is always the first one
         * regardless of the actually displayed selected
         * map.
         */
        int wantedMapIndex = 0;

        int oldAmountOfComPorts = 0;

        bool requiresNewDrawing = true;

        Controller* GetHardwareController(int controllerTypeNumber);

        int UpdateKeyboardControllers();

        int GetDetectedMuons();
        bool ResetDetectedMuons();
        bool SetMessage(std::string LCDmessage);

        void SetNewQMenu(int newQMenuIndex);

        int amountOfAvailablePorts = 0;

        BomberManGame* currentGame;

        QColor* colorPlayerA;
        QColor* colorPlayerB;
        QColor* colorPlayerC;
        QColor* colorPlayerD;
        QColor* colorPlayerE;

        bool useAccelerometer = false;
        bool useMuons = false;
};

#include "../Game/Game.h"