#include "AppHandler.h"

// - FUNCTIONS - //
Controller* AppHandler::GetHardwareController(int controllerTypeNumber)
{
    switch(controllerTypeNumber)
    {
        case(CONTROLLER_TYPE_ARDUINO_A):    return arduinoThread.GetArduino()->GetPlayerController(0);
        case(CONTROLLER_TYPE_ARDUINO_B):    return arduinoThread.GetArduino()->GetPlayerController(1);
        case(CONTROLLER_TYPE_KEYBOARD_A):    return &letterKeyboard;
        case(CONTROLLER_TYPE_KEYBOARD_B):    return &numpadKeyboard;
    }
    return arduinoThread.GetArduino()->GetPlayerController(0);
}

int AppHandler::UpdateKeyboardControllers()
{
    numpadKeyboard.isConnected = true;
    letterKeyboard.isConnected = true;

    if(GetAsyncKeyState(CONTROLLER_KEYBOARD_A_Y_T) & 0x8000) letterKeyboard.joystickY = 100;
    if(GetAsyncKeyState(CONTROLLER_KEYBOARD_A_Y_B) & 0x8000) letterKeyboard.joystickY = 0;  
    if(GetAsyncKeyState(CONTROLLER_KEYBOARD_A_X_L) & 0x8000) letterKeyboard.joystickX = 100;
    if(GetAsyncKeyState(CONTROLLER_KEYBOARD_A_X_R) & 0x8000) letterKeyboard.joystickX = 0;
    if(!(GetAsyncKeyState(CONTROLLER_KEYBOARD_A_X_R) & 0x8000) && !(GetAsyncKeyState(CONTROLLER_KEYBOARD_A_X_L) & 0x8000)) letterKeyboard.joystickX = 50;
    if(!(GetAsyncKeyState(CONTROLLER_KEYBOARD_A_Y_T) & 0x8000) && !(GetAsyncKeyState(CONTROLLER_KEYBOARD_A_Y_B) & 0x8000)) letterKeyboard.joystickY = 50;

    letterKeyboard.leftButton       = (GetAsyncKeyState(CONTROLLER_KEYBOARD_A_LEFT)   & 0x8000);
    letterKeyboard.rightButton      = (GetAsyncKeyState(CONTROLLER_KEYBOARD_A_RIGHT)  & 0x8000);
    letterKeyboard.topButton        = (GetAsyncKeyState(CONTROLLER_KEYBOARD_A_UP)     & 0x8000);
    letterKeyboard.bottomButton     = (GetAsyncKeyState(CONTROLLER_KEYBOARD_A_DOWN)   & 0x8000);
    letterKeyboard.joystickButton   = (GetAsyncKeyState(CONTROLLER_KEYBOARD_A_SELECT) & 0x8000);

    if(GetAsyncKeyState(CONTROLLER_KEYBOARD_B_Y_T) & 0x8000) numpadKeyboard.joystickY = 100;
    if(GetAsyncKeyState(CONTROLLER_KEYBOARD_B_Y_B) & 0x8000) numpadKeyboard.joystickY = 0;  
    if(GetAsyncKeyState(CONTROLLER_KEYBOARD_B_X_L) & 0x8000) numpadKeyboard.joystickX = 100;
    if(GetAsyncKeyState(CONTROLLER_KEYBOARD_B_X_R) & 0x8000) numpadKeyboard.joystickX = 0;
    if(!(GetAsyncKeyState(CONTROLLER_KEYBOARD_B_X_R) & 0x8000) && !(GetAsyncKeyState(CONTROLLER_KEYBOARD_B_X_L) & 0x8000)) numpadKeyboard.joystickX = 50;
    if(!(GetAsyncKeyState(CONTROLLER_KEYBOARD_B_Y_T) & 0x8000) && !(GetAsyncKeyState(CONTROLLER_KEYBOARD_B_Y_B) & 0x8000)) numpadKeyboard.joystickY = 50;

    numpadKeyboard.leftButton       = (GetAsyncKeyState(CONTROLLER_KEYBOARD_B_LEFT)   & 0x8000);
    numpadKeyboard.rightButton      = (GetAsyncKeyState(CONTROLLER_KEYBOARD_B_RIGHT)  & 0x8000);
    numpadKeyboard.topButton        = (GetAsyncKeyState(CONTROLLER_KEYBOARD_B_UP)     & 0x8000);
    numpadKeyboard.bottomButton     = (GetAsyncKeyState(CONTROLLER_KEYBOARD_B_DOWN)   & 0x8000);
    numpadKeyboard.joystickButton   = (GetAsyncKeyState(CONTROLLER_KEYBOARD_B_SELECT) & 0x8000);
    return 1;
}

AppHandler::AppHandler()
{

}

int AppHandler::GetDetectedMuons()
{
    return arduinoThread.GetArduino()->GetMuonCount();
}

bool AppHandler::ResetDetectedMuons()
{
    return arduinoThread.GetArduino()->ResetMuons();
}