/**
 * @file ExitMenu.cpp
 * @author LyamBRS
 * @brief
 * Header definition of the ExitMenu class
 * which allows a ExitMenu to be handled.
 * @version 0.1
 * @date 2024-02-15
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "ExitMenu.h"

// - DEFINES - //

// - CLASS - //

cExitMenu::cExitMenu(AppHandler* currentAppHandler)
{
    appRef = currentAppHandler;
}

bool cExitMenu::Update()
{
    return false;
}

bool cExitMenu::HandleKeyboard(int keyBoardKey)
{
    switch (keyBoardKey)
    {    
        case KB_RIGHT:
                selection--;
                if(selection<0) selection=1;
                return true;            
    
        case KB_LEFT:
                selection++;
                if(selection>1) selection=0;
                return true;                  

        case KB_ENTER:
                if(selection==0) appRef->currentSelectedMenu = 0;
                if(selection==1) appRef->wantedSelectedMenu = -1;
                selection = 0;
                return true;
    }        
    return false;
}

bool cExitMenu::OnEnter()
{
    needsToBeRedrawn = true;
    return true;
}

bool cExitMenu::OnExit()
{
    needsToBeRedrawn = true;
    return true;
}

bool cExitMenu::Draw()
{
    ResizeTerminal(36, 9);
    if(needsToBeRedrawn)
    {
        needsToBeRedrawn = false;
        system("cls");
    }
    SetTerminalCursorPosition(0,0);
	std::cout << "############################################" << std::endl;
    std::cout << "                - BomberMan -               " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    std::cout << "-      Are you sure you want to exit?     - " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;

    switch(selection)
    {
        case(0):
            std::cout << "            ";
            PrintInColour(std::cout, "[NO]",       colors::white, colors::blue);
            std::cout << "           ";
            PrintInColour(std::cout, "[YES]\n",       colors::grey, colors::black);
            appRef->SetMessage("    Go back?    ");
            break;

        case(1):
            std::cout << "            ";
            PrintInColour(std::cout, "[NO]",       colors::grey, colors::black);
            std::cout << "           ";
            PrintInColour(std::cout, "[YES]\n",       colors::white, colors::blue);
            appRef->SetMessage("     Leave?     ");
            break;
    }
    std::cout << "############################################" << std::endl;
    return true;
}
