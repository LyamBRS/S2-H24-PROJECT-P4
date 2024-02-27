/**
 * @file TestMenu.cpp
 * @author LyamBRS
 * @brief
 * Header definition of the TestMenu class
 * which allows a TestMenu to be handled.
 * @version 0.1
 * @date 2024-02-15
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "TestMenu.h"

// - DEFINES - //

// - CLASS - //

bool TestMenu::DrawNoArduinoMenu()
{
    system("cls");
	std::cout << "############################################" << std::endl;
    std::cout << "            - Application Tests -           " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    PrintInColour(std::cout, "     No Arduino is  currently connected     \n", colors::white, colors::red);
	std::cout << "--------------------------------------------" << std::endl;
    std::cout << "                    ";
    PrintInColour(std::cout, "[OK]\n", colors::black, colors::aqua);
	std::cout << "############################################" << std::endl;
    return true;
}

bool TestMenu::DrawMainTestMenu()
{
    system("cls");
	std::cout << "############################################" << std::endl;
    std::cout << "            - Application Tests -           " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    std::cout << "- Navigate to choose your application test -" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;

    auto drawASelection = [](int selection, std::string name, bool isSelected)
    {
        if(isSelected)
        {
            PrintInColour(std::cout, "-> ", colors::aqua, colors::black);
            PrintInColour(std::cout, name, colors::aqua, colors::black);     
        }
        else
        {
            PrintInColour(std::cout, "   ", colors::white, colors::black);
            PrintInColour(std::cout, name, colors::grey, colors::black);    
        }
        std::cout << std::endl;
    };

    std::string menus[] = {
        "LCD tests",
        "Bargraph tests",
        "Raw RX display",
        "Parsed controller display",
        "Back to main menu"
    };

    for(int i=0; i<5; ++i)
    {
        drawASelection(selection, menus[i], selection==i);
    }
	std::cout << "############################################" << std::endl;

    return true;
}

bool TestMenu::DrawLCDTestMenu()
{
    system("cls");
	std::cout << "############################################" << std::endl;
    std::cout << "            - Application Tests -           " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    std::cout << "- Write new sentence to display on the LCD -" << std::endl;
    std::cout << "-   Sentence must be  20 characters long   -" << std::endl;
    std::cout << "-    Press enter to  send, esc to leave    -" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    std::cout << "- ";

    // CURRENT MESSAGE
    PrintInColour(std::cout, "Current Message: ", colors::lightgrey, colors::black);
    PrintInColour(std::cout, appRef->arduinoThread.GetArduino()->GetLCDMessage(), colors::darkpurple, colors::black);
    std::cout << std::endl;
    std::cout << "- ";

    // CHARACTER LEFT
    PrintInColour(std::cout, "Characters left: ", colors::lightgrey, colors::black);
    PrintInColour(std::cout, std::to_string(20-newLCDMessage.length()), colors::darkpurple, colors::black);
    std::cout << std::endl;


    #define LCD_NO_ERROR 0
    #define LCD_REMOVED_A_LETTER 1
    #define LCD_ADDED_A_LETTER 2
    #define LCD_ALREADY_EMPTY 3
    #define LCD_MESSAGE_TOO_LONG 4
    #define LCD_MESSAGE_MUST_BE_20_LONG 5
    #define LCD_INCORRECT_KEYBOARD 6
	std::cout << "--------------------------------------------" << std::endl;
    switch(selection)
    {
        case(LCD_NO_ERROR):                 PrintInColour(std::cout, "-                NO  ERRORS                -", colors::white, colors::black); break;
        case(LCD_REMOVED_A_LETTER):         PrintInColour(std::cout, "-       Letters successfully removed       -", colors::leaf, colors::black); break;
        case(LCD_ADDED_A_LETTER):           PrintInColour(std::cout, "-        Letters successfully added        -", colors::leaf, colors::black); break;
        case(LCD_ALREADY_EMPTY):            PrintInColour(std::cout, "-  No need,  the message is already empty  -", colors::gold, colors::black); break;
        case(LCD_MESSAGE_TOO_LONG):         PrintInColour(std::cout, "- Message's lenght of  20 already acheived -", colors::gold, colors::black); break;
        case(LCD_MESSAGE_MUST_BE_20_LONG):  PrintInColour(std::cout, "-    Your message must be 20 characters    -", colors::red, colors::black); break;
        case(LCD_INCORRECT_KEYBOARD):       PrintInColour(std::cout, "- INVALID KEY PRESSED.  WATCHU DOING BREH? -", colors::white, colors::red); break;
        case(LCD_MESSAGE_UPDATED):          PrintInColour(std::cout, "-      YOUR MESSAGE IS NOW BEING SENT      -", colors::black, colors::green); break;
    }
    std::cout << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    std::cout << newLCDMessage;
    return true;
}

bool TestMenu::DrawBarGraphTestMenu()
{
    auto drawABarGraph = [](int bargraphBits)
    {
        for(int i=0; i<10; ++i)
        {
            bool result = bargraphBits&(1<<i);
            if(i<3) // GREEN
            {
                if(result)
                {
                    PrintInColour(std::cout, " ", colors::black, colors::green);
                }
                else
                {
                    PrintInColour(std::cout, " ", colors::black, colors::grey);
                }
            }
            else if(i<7) // YELLOW
            {
                if(result)
                {
                    PrintInColour(std::cout, " ", colors::black, colors::gold);
                }
                else
                {
                    PrintInColour(std::cout, " ", colors::black, colors::grey);
                }
            }
            else // RED
            {
                if(result)
                {
                    PrintInColour(std::cout, " ", colors::black, colors::red);
                }
                else
                {
                    PrintInColour(std::cout, " ", colors::black, colors::grey);
                }
            }
        }
    };

    system("cls");
	std::cout << "############################################" << std::endl;
    std::cout << "            - Application Tests -           " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    std::cout << "- Decide new bargraphs display for players -" << std::endl;
    std::cout << "-    Select LEDS with left/right arrows    -" << std::endl;
    std::cout << "-      Turn them ON/OFF  with up/down      -" << std::endl;
    std::cout << "-    Press enter to  send, esc to leave    -" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    PrintInColour(std::cout, bargraphMessage, colors::darkpurple, colors::black);
	std::cout << "\n--------------------------------------------" << std::endl;
    std::cout << "- ";

    int bitsA = appRef->arduinoThread.GetArduino()->GetPlayerController(0)->barGraphBits;
    int bitsB = appRef->arduinoThread.GetArduino()->GetPlayerController(1)->barGraphBits;

    if(bitsA > 0b1111111111 || bitsA<0)
    {
        appRef->arduinoThread.GetArduino()->GetPlayerController(0)->barGraphBits = 0;
        bitsA = 0;
    }

    if(bitsB > 0b1111111111 || bitsB<0)
    {
        appRef->arduinoThread.GetArduino()->GetPlayerController(1)->barGraphBits = 0;
        bitsB = 0;
    }

    PrintInColour(std::cout, "Current PlayerA: ", colors::grey, colors::black);
    PrintInColour(std::cout, std::to_string(bitsA), colors::darkpurple, colors::black);
    std::cout << ":\t";
    drawABarGraph(bitsA);
    std::cout << std::endl;
    std::cout << "- ";

    PrintInColour(std::cout, "Current PlayerB: ", colors::grey, colors::black);
    PrintInColour(std::cout, std::to_string(bitsB), colors::darkpurple, colors::black);
    std::cout << ":\t";
    drawABarGraph(bitsB);
    std::cout << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    
    // UPPER ARROWS, PLAYER A
    std::cout << " ";
    for(int i=0; i<10; ++i)
    {
        if(selection==i)
        {
            PrintInColour(std::cout, "^", colors::aqua, colors::black);
        }
        else
        {
            PrintInColour(std::cout, "^", colors::grey, colors::black);        
        }
    }

    // UPPER ARROWS, PLAYER B
    std::cout << " ";
    for(int i=0; i<10; ++i)
    {
        if(selection==i+10)
        {
            PrintInColour(std::cout, "^", colors::aqua, colors::black);
        }
        else
        {
            PrintInColour(std::cout, "^", colors::grey, colors::black);        
        }
    }
    std::cout << std::endl;
    std::cout << " ";
    drawABarGraph(wantedBitsPlayerA);
    std::cout << " ";
    drawABarGraph(wantedBitsPlayerB);
    std::cout << std::endl;
	std::cout << "############################################" << std::endl;
    return true;
}

bool TestMenu::DrawReceivedMessageMenuKeyboard()
{
    system("cls");
	std::cout << "############################################" << std::endl;
    std::cout << "            - Application Tests -           " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    std::cout << "- Displays RAW data  received from arduino -" << std::endl;
    std::cout << "-            Press esc to leave            -" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    return true;
}

bool TestMenu::DrawControllerMenu()
{
    return false;
}




bool TestMenu::HandleNoArduinoMenu(int keyBoardKey)
{
    appRef->currentSelectedMenu = APP_MAIN_MENU;
    return false;
}

bool TestMenu::HandleMainTestMenuKeyboard(int keyBoardKey)
{
    switch (keyBoardKey)
    {    
        case KB_UP:
                selection--;
                if(selection<APP_MIN_SUBMENU) selection=4;
                return true;            
    
        case KB_DOWN:
                selection++;
                if(selection>4) selection=APP_MIN_SUBMENU;
                return true;

        case KB_ESCAPE:
                appRef->currentSelectedMenu = APP_MAIN_MENU;
                selectedSubMenu = APP_MAIN_MENU;
                selection = 0;
                return true;

        case KB_ENTER:
                switch(selection)
                {
                    case(0): selectedSubMenu = APP_LCD; return true;
                    case(1): selectedSubMenu = APP_BARGRAPH; return true;
                    case(2): selectedSubMenu = APP_RECEIVED_MESSAGE; return true;
                    case(3): selectedSubMenu = APP_CONTROLLER; return true;
                    case(4): appRef->currentSelectedMenu = APP_MAIN_MENU; return true;
                }
                return false;
    }
    return false;
}

bool TestMenu::HandleLCDTestMenuKeyboard(int keyBoardKey)
{
    switch (keyBoardKey)
    {
        case KB_LEFT:
        case KB_UP:
        case KB_DOWN:
        case KB_RIGHT:
            selection = LCD_INCORRECT_KEYBOARD;
            return true;

        case KB_ESCAPE:
                selectedSubMenu = APP_MAIN_MENU;
                selection = LCD_NO_ERROR;
                return true;

        case KB_DEL:
        case KB_BACK:
                if(newLCDMessage.size() == 0)
                {
                    selection = LCD_ALREADY_EMPTY;
                    return true;
                }
                newLCDMessage.erase(newLCDMessage.size()-1);
                selection = LCD_REMOVED_A_LETTER;
                return true;

        case KB_ENTER:
                if(newLCDMessage.length() != 20)
                {
                    selection = LCD_MESSAGE_MUST_BE_20_LONG;
                    return true;
                }
                selection = LCD_MESSAGE_UPDATED;
                appRef->arduinoThread.GetArduino()->SetNewLCDMessage(newLCDMessage);
                return true;
    }
    if(keyBoardKey>31 && keyBoardKey<127)
    {
        if(newLCDMessage.length() >= 20)
        {
            selection = LCD_MESSAGE_TOO_LONG;
            return true;
        }
        newLCDMessage += static_cast<char>(keyBoardKey);
        selection = LCD_ADDED_A_LETTER;
        return true;
    }
    else
    {
        selection = LCD_INCORRECT_KEYBOARD;
        return true;
    }

    return false;
}

bool TestMenu::HandleBarGraphTestMenuKeyboard(int keyBoardKey)
{
    switch (keyBoardKey)
    {    
        case KB_UP:
        case KB_DOWN:
                bargraphMessage = "";
                bargraphMessage = "   Switched player";

                if(selection>9)
                {
                    bargraphMessage.append("B's  LED number ");
                    bargraphMessage.append(std::to_string(selection-10));
                    bargraphMessage.append(" state");
                }
                else
                {
                    bargraphMessage.append("A's LED number ");
                    bargraphMessage.append(std::to_string(selection));
                    bargraphMessage.append(" state");
                }

                switch(selection)
                {
                    case(0): wantedBitsPlayerA = wantedBitsPlayerA ^= 1; return true;
                    case(1): wantedBitsPlayerA = wantedBitsPlayerA ^= 2; return true;
                    case(2): wantedBitsPlayerA = wantedBitsPlayerA ^= 4; return true;
                    case(3): wantedBitsPlayerA = wantedBitsPlayerA ^= 8; return true;
                    case(4): wantedBitsPlayerA = wantedBitsPlayerA ^= 16; return true;
                    case(5): wantedBitsPlayerA = wantedBitsPlayerA ^= 32; return true;
                    case(6): wantedBitsPlayerA = wantedBitsPlayerA ^= 64; return true;
                    case(7): wantedBitsPlayerA = wantedBitsPlayerA ^= 128; return true;
                    case(8): wantedBitsPlayerA = wantedBitsPlayerA ^= 256; return true;
                    case(9): wantedBitsPlayerA = wantedBitsPlayerA ^= 512; return true;

                    case(10): wantedBitsPlayerB = wantedBitsPlayerB ^= 1; return true;
                    case(11): wantedBitsPlayerB = wantedBitsPlayerB ^= 2; return true;
                    case(12): wantedBitsPlayerB = wantedBitsPlayerB ^= 4; return true;
                    case(13): wantedBitsPlayerB = wantedBitsPlayerB ^= 8; return true;
                    case(14): wantedBitsPlayerB = wantedBitsPlayerB ^= 16; return true;
                    case(15): wantedBitsPlayerB = wantedBitsPlayerB ^= 32; return true;
                    case(16): wantedBitsPlayerB = wantedBitsPlayerB ^= 64; return true;
                    case(17): wantedBitsPlayerB = wantedBitsPlayerB ^= 128; return true;
                    case(18): wantedBitsPlayerB = wantedBitsPlayerB ^= 256; return true;
                    case(19): wantedBitsPlayerB = wantedBitsPlayerB ^= 512; return true;
                }
                return true;

        case KB_RIGHT:
            selection++;
            if(selection>19) selection = 0;

            bargraphMessage = "";
            bargraphMessage = "     Selected player";

            if(selection>9)
            {
                bargraphMessage.append("B's  LED number ");
                bargraphMessage.append(std::to_string(selection-10));
            }
            else
            {
                bargraphMessage.append("A's LED number ");
                bargraphMessage.append(std::to_string(selection));
            }
            return true;

        case KB_LEFT:
            selection--;
            if(selection<0) selection = 19;

            bargraphMessage = "";
            bargraphMessage = "     Selected player";

            if(selection>9)
            {
                bargraphMessage.append("B's LED number ");
                bargraphMessage.append(std::to_string(selection-10));
            }
            else
            {
                bargraphMessage.append("A's LED number ");
                bargraphMessage.append(std::to_string(selection));
            }

            return true;      

        case KB_ESCAPE:
                selectedSubMenu = APP_MAIN_MENU;
                selection = 0;
                return true;

        case KB_ENTER:
                bargraphMessage = "         Updated sent bargraph data";
                appRef->arduinoThread.GetArduino()->GetPlayerController(0)->barGraphBits = wantedBitsPlayerA;
                appRef->arduinoThread.GetArduino()->GetPlayerController(1)->barGraphBits = wantedBitsPlayerB;
                return false;
    }
    return false;
}

bool TestMenu::HandleReceivedMessageMenuKeyboard(int keyBoardKey)
{
    switch (keyBoardKey)
    {    
        case KB_ESCAPE:
                appRef->currentSelectedMenu = APP_MAIN_MENU;
                selectedSubMenu = APP_MAIN_MENU;
                selection = 0;
                return true;
    }
    return false;
}

bool TestMenu::HandleControllerMenuKeyboard(int keyBoardKey)
{
    return false;
}












TestMenu::TestMenu(AppHandler* currentAppHandler)
{
    appRef = currentAppHandler;
}

bool TestMenu::HandleKeyboard(int keyBoardKey)
{
    switch(selectedSubMenu)
    {
        case(APP_RECEIVED_MESSAGE): HandleReceivedMessageMenuKeyboard(keyBoardKey); return true;
        case(APP_NO_ARDUINO): HandleNoArduinoMenu(keyBoardKey); return true;
        case(APP_BARGRAPH): HandleBarGraphTestMenuKeyboard(keyBoardKey); return true;
        case(APP_LCD): HandleLCDTestMenuKeyboard(keyBoardKey); return true;
        case(APP_MAIN): HandleMainTestMenuKeyboard(keyBoardKey); return true;
        case(APP_CONTROLLER): HandleControllerMenuKeyboard(keyBoardKey); return true;
    }
    return false;
}

bool TestMenu::Draw()
{
    switch(selectedSubMenu)
    {
        case(APP_RECEIVED_MESSAGE): DrawReceivedMessageMenuKeyboard(); return true;
        case(APP_NO_ARDUINO): DrawNoArduinoMenu(); return true;
        case(APP_BARGRAPH): DrawBarGraphTestMenu(); return true;
        case(APP_LCD): DrawLCDTestMenu(); return true;
        case(APP_MAIN): DrawMainTestMenu(); return true;
        case(APP_CONTROLLER): DrawControllerMenu(); return true;
    }
    return false;
}

bool TestMenu::OnEnter()
{
    selection = 0;
    return false;
}

bool TestMenu::OnExit()
{
    selection = 0;
    return false;
}

bool TestMenu::Update()
{
    static std::string currentMessage = "";
    static std::string oldMessage = "";

    if(!appRef->arduinoThread.GetArduino()->GetPortState())
    {
        selectedSubMenu = APP_NO_ARDUINO;
        selection = 0;
    }
    else
    {
        if(selectedSubMenu == APP_NO_ARDUINO)
        {
            selectedSubMenu = APP_MAIN;
        }
    }

    currentMessage = appRef->arduinoThread.GetArduino()->GetLastRawMessage();
    if(oldMessage != currentMessage)
    {
        oldMessage = currentMessage;
        if(selectedSubMenu == APP_RECEIVED_MESSAGE)
        {
            PrintInColour(std::cout, currentMessage, colors::aqua, colors::black);
            std::cout << "\r" << std::flush;  
        }
    }

    return true;
}