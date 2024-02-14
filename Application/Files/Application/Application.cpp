/**
 * @file Application.cpp
 * @author LyamBRS
 * @brief
 * File containing the basic test
 * application program of the
 * Application.
 * @version 0.1
 * @date 2024-02-14
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "Application.h"

// - PROGRAM - //
/**
 * @brief 
 * Simple function which handles the arrow keys
 * of the user as well as the enter key so that
 * navigation is possible between menus.
 * @return true:
 * Successfully handled a valid key.
 * @return false:
 * Invalid key.
 */
bool Application::HandleKeyboardActions()
{
    if (kbhit())
    {
        requiresNewDrawing = true;
        switch(currentSelectedMenu)
        {
            case(APP_ARDUINO_MENU):
                ArduinoSetupKeyboardHandler();
                break;
            
            case(APP_MAIN_MENU):
                MainMenuKeyboardHandler();
                break;

            case(APP_EXIT_MENU):
                ExitMenuKeyboardHandler();
                break;

            case(APP_GAME_MENU):
                GameMenuKeyboardHandler();
                break;

            case(APP_TEST_MENU):
                TestMenuKeyboardHandler();
                break;
        } 
    }
    return true;
}

bool Application::MainMenuKeyboardHandler()
{
    int keyboardCode = getch();    
    switch (keyboardCode)
    {    
        case KB_UP:
                wantedSelectedMenu--;
                if(wantedSelectedMenu<0) wantedSelectedMenu=0;
                return true;            
    
        case KB_DOWN:
                wantedSelectedMenu++;
                if(wantedSelectedMenu>4) wantedSelectedMenu=4;
                return true;                  

        case KB_ENTER:
                selection = 0;
                currentSelectedMenu = wantedSelectedMenu;
                return true;
    }        
    return false;
}

bool Application::TestMenuKeyboardHandler()
{
    return false;
}

bool Application::ExitMenuKeyboardHandler()
{
    int keyboardCode = getch();    
    switch (keyboardCode)
    {    
        case KB_UP:
                selection--;
                if(selection<0) selection=0;
                return true;            
    
        case KB_DOWN:
                selection++;
                if(selection>1) selection=1;
                return true;                       

         case KB_LEFT:
                selection--;
                if(selection<0) selection=0;
                return true;            
    
        case KB_RIGHT:
                selection++;
                if(selection>1) selection=1;
                return true;

        case KB_ENTER:
                if(selection==0) currentSelectedMenu = APP_MAIN_MENU;
                if(selection==1) wantedSelectedMenu = -1;
                return true;
    }        
    return false;
}

bool Application::GameMenuKeyboardHandler()
{
    return false;
}

bool Application::ArduinoSetupKeyboardHandler()
{
    return false;
}

/**
 * @brief 
 * Draws the menu that allows the user to select
 * a wanted com port as well as a wanted baud rate
 * and see if their connection was successful or not.
 * @return true 
 * @return false 
 */
bool Application::DrawArduinoSetupMenu()
{
    return false;
}

/**
 * @brief 
 * Draws the little prompt which asks the user
 * if they really want to leave the application.
 * @return true 
 * @return false 
 */
bool Application::DrawExitMenu()
{
    system("cls");
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
            break;

        case(1):
            std::cout << "            ";
            PrintInColour(std::cout, "[NO]",       colors::grey, colors::black);
            std::cout << "           ";
            PrintInColour(std::cout, "[YES]\n",       colors::white, colors::blue);
            break;
    }
    std::cout << "############################################" << std::endl;
    return true;
}

/**
 * @brief 
 * Draws a simple main menu where the user can
 * select what they want to do by pressing a
 * number on their terminal.
 * @return true:
 * Successfully drew the main menu.
 * @return false:
 * Failed to draw the main menu.
 */
bool Application::DrawMainMenu()
{
    system("cls");
	std::cout << "############################################" << std::endl;
    std::cout << "                - BomberMan -               " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    std::cout << "-  Press the arrow keys to navigate menus - " << std::endl;
    std::cout << "- Press enter to select  the current thing -" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;

    switch(wantedSelectedMenu)
    {
        case(APP_MAIN_MENU):
            PrintInColour(std::cout, "-> 0: Main Menu\n",       colors::aqua, colors::black);
            PrintInColour(std::cout, "   1: Test Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "   2: Arduino setup\n",   colors::grey, colors::black);
            PrintInColour(std::cout, "   3: Game Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "   4: Exit Menu\n",       colors::grey, colors::black);
            break;

        case(APP_GAME_MENU):
            PrintInColour(std::cout, "   0: Main Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "   1: Test Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "   2: Arduino setup\n",   colors::grey, colors::black);
            PrintInColour(std::cout, "-> 3: Game Menu\n",       colors::aqua, colors::black);
            PrintInColour(std::cout, "   4: Exit Menu\n",       colors::grey, colors::black);
            break;

        case(APP_TEST_MENU):
            PrintInColour(std::cout, "   0: Main Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "-> 1: Test Menu\n",       colors::aqua, colors::black);
            PrintInColour(std::cout, "   2: Arduino setup\n",   colors::grey, colors::black);
            PrintInColour(std::cout, "   3: Game Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "   4: Exit Menu\n",       colors::grey, colors::black);
            break;

        case(APP_EXIT_MENU):
            PrintInColour(std::cout, "   0: Main Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "   1: Test Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "   2: Arduino setup\n",   colors::grey, colors::black);
            PrintInColour(std::cout, "   3: Game Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "-> 4: Exit Menu\n",       colors::red, colors::black);
            break;

        case(APP_ARDUINO_MENU):
            PrintInColour(std::cout, "   0: Main Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "   1: Test Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "-> 2: Arduino setup\n",   colors::aqua, colors::black);
            PrintInColour(std::cout, "   3: Game Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "   4: Exit Menu\n",       colors::grey, colors::black);
            break;
    }
    std::cout << "############################################" << std::endl;
    return true;
}

/**
 * @brief 
 * Draw the arduino communication test menu
 * where the user can see what their Arduino
 * is answering to a handshake request by
 * printing JSON on the terminal.
 * @return true:
 * Successfully drew communication test
 * menu.
 * @return false:
 * Failed to draw communication test menu. 
 */
bool Application::DrawCommTestMenu()
{
    return false;
}

/**
 * @brief 
 * Draw the menu where the user can select which
 * map they want to play to eventually start the
 * game so that they can play it.
 * @return true:
 * Successfully drew the game menu.
 * @return false:
 * Failed to draw the game menu.
 */
bool Application::DrawGameMenu()
{
    return false;
}

/**
 * @brief 
 * Handles all the drawing of all the menus
 * Specifies if they need to be redrawn as well.
 * @return true 
 * @return false 
 */
bool Application::HandleMenuDrawings()
{
    if(requiresNewDrawing)
    {
        switch(currentSelectedMenu)
        {
            case(APP_ARDUINO_MENU):
                DrawArduinoSetupMenu();
                break;
    
            case(APP_EXIT_MENU):
                DrawExitMenu();
                break;
    
            case(APP_GAME_MENU):
                DrawGameMenu();
                break;
    
            case(APP_MAIN_MENU):
                DrawMainMenu();
                break;
    
            case(APP_TEST_MENU):
                DrawCommTestMenu();
                break;
        }
        requiresNewDrawing = false;
    }
    return true;
}

/**
 * @brief
 * # Application
 * @brief
 * Class used to create one application.
 * The application allow you to setup your Arduino
 * and setup your game. It handles basic terminal
 * menus as well.
 */
Application::Application()
{

}

/**
 * @brief 
 * Updates the application each QT frames.
 * Calls all the Update functions of all the
 * things in the application.
 * @return true:
 * Successfully updated all the application.
 * @return false:
 * Failed to update all the application.
 */
bool Application::Update()
{
    HandleMenuDrawings();
    HandleKeyboardActions();

    arduino.Update();
    currentGame.Update();
    return true;
}

/**
 * @brief 
 * Debug loop executed until the terminal
 * application wants to close.
 */
void Application::TemporaryLoop()
{
    while(wantedSelectedMenu != -1)
    {
        Sleep(100);
        Update();
    }
}