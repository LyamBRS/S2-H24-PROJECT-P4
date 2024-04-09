/**
 * @file MainMenu.cpp
 * @author LyamBRS
 * @brief
 * Header definition of the MainMenu class
 * which allows a MainMenu to be handled.
 * @version 0.1
 * @date 2024-02-15
 * @copyright Copyright (c) 2024
 */


// - INCLUDES - //
#include "MainMenu.h"

// - DEFINES - //

// - CLASS - //
cMainMenu::cMainMenu(AppHandler* currentAppHandler)
{
    appRef = currentAppHandler;
}

bool cMainMenu::Update()
{
    return false;
}

bool cMainMenu::OnEnter()
{
    oldSelection = -1;
    return true;
}

bool cMainMenu::OnExit()
{
    oldSelection = -1;
    return true;
}

bool cMainMenu::HandleKeyboard(int keyBoardKey)
{
    switch (keyBoardKey)
    {    
        case KB_UP:
                selection--;
                if(selection<1) selection=APP_AMOUNT_OF_MENUS;
                return true;            
    
        case KB_DOWN:
                selection++;
                if(selection>APP_AMOUNT_OF_MENUS) selection=1;
                return true;                  

        case KB_ENTER:
                appRef->currentSelectedMenu = selection;
                selection = 0;
                return true;
        
        case KB_ESCAPE:
                appRef->currentSelectedMenu = APP_EXIT_MENU;
                selection = 0;
                return true; 
    }        
    return false;
}

bool cMainMenu::Draw()
{
    if(oldSelection != appRef->currentSelectedMenu)
    {
        oldSelection = appRef->currentSelectedMenu;
        ResizeTerminal(36, 12);
        system("cls");
    }
    ResizeTerminal(36, 12);
    SetTerminalCursorPosition(0,0);
	std::cout << "############################################" << std::endl;
    std::cout << "                - BomberMan -               " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    std::cout << "-  Press the arrow keys to navigate menus  - " << std::endl;
    std::cout << "-   Enter key: select the current option   -" << std::endl;
    std::cout << "-   Esc key: return to the previous menu   -" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;

    // if not done, the available menus are not printed until a key is pressed
    if(selection == 0)
    {
        selection = 1;
    }

    if(!appRef->arduinoThread.GetArduino()->GetPortState())                              PrintInColour(std::cout, "-      No arduino connected to the PC      -", colors::red, colors::black);
    if(appRef->arduinoThread.GetArduino()->GetPortState() && !appRef->arduinoThread.GetArduino()->Verify())  PrintInColour(std::cout, "- Connected devices not answering requests -", colors::black, colors::gold);
    if(appRef->arduinoThread.GetArduino()->GetPortState() && appRef->arduinoThread.GetArduino()->Verify())  PrintInColour(std::cout, "-     Connected arduino is operational     -", colors::black, colors::green);
    std::cout << std::endl;

	std::cout << "--------------------------------------------" << std::endl;

    switch(selection)
    {
        case(APP_MAP_MENU):
            PrintInColour(std::cout, "   1: Test Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "   2: Arduino setup\n",   colors::grey, colors::black);
            PrintInColour(std::cout, "-> 3: Game Menu\n",       colors::aqua, colors::black);
            PrintInColour(std::cout, "   4: Exit Menu\n",       colors::grey, colors::black);
            appRef->SetMessage("3:     Game menu");
            break;

        case(APP_TEST_MENU):
            PrintInColour(std::cout, "-> 1: Test Menu\n",       colors::aqua, colors::black);
            PrintInColour(std::cout, "   2: Arduino setup\n",   colors::grey, colors::black);
            PrintInColour(std::cout, "   3: Game Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "   4: Exit Menu\n",       colors::grey, colors::black);
            appRef->SetMessage("1:     Test menu");
            break;

        case(APP_EXIT_MENU):
            PrintInColour(std::cout, "   1: Test Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "   2: Arduino setup\n",   colors::grey, colors::black);
            PrintInColour(std::cout, "   3: Game Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "-> 4: Exit Menu\n",       colors::red, colors::black);
            appRef->SetMessage("4:     Exit menu");
            break;

        case(APP_ARDUINO_MENU):
            PrintInColour(std::cout, "   1: Test Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "-> 2: Arduino setup\n",   colors::aqua, colors::black);
            PrintInColour(std::cout, "   3: Game Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "   4: Exit Menu\n",       colors::grey, colors::black);
            appRef->SetMessage("2:  Arduino menu");
            break;
    }
    std::cout << "############################################" << std::endl;
    return true;
}