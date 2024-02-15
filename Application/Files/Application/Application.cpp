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

            case(APP_BAUD_RATE_MENU):
                ArduinoBaudRateKeyboardHandler();
                break;

            case(APP_COM_PORT_MENU):
                ArduinoComPortKeyboardHandler();
                break;

            case(APP_CONNECTING_MENU):
                ArduinoConnectingKeyboardHandler();
                break;

            case(APP_DISCONNECTING_MENU):
                ArduinoDisconnectingKeyboardHandler();
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
                if(wantedSelectedMenu<1) wantedSelectedMenu=4;
                return true;            
    
        case KB_DOWN:
                wantedSelectedMenu++;
                if(wantedSelectedMenu>4) wantedSelectedMenu=1;
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
    int keyboardCode = getch();

    // Avoid being able to change baudrate and port when its currently connected.
    if(selection < 3 && arduino.GetPortState())
    {
        selection = 3;
    }

    switch (keyboardCode)
    {    
        case KB_UP:
                selection--;
                if(selection<0) selection=4;

                // Dont hover over Disconnect if it cant be disconnected
                if(selection == 3 && !arduino.GetPortState())
                {
                    selection = 2;
                }

                // Avoid being able to change baudrate and port when its currently connected.
                if(selection < 3 && arduino.GetPortState())
                {
                    selection = 3;
                }

                return true;            
    
        case KB_DOWN:
                selection++;

                // Dont hover over Disconnect if it cant be disconnected
                if(selection == 3 && !arduino.GetPortState())
                {
                    selection = 4;
                }

                if(selection>4) selection=0;
                return true;

        case KB_ENTER:
                if(selection==4) currentSelectedMenu = APP_MAIN_MENU;
                if(selection==0) currentSelectedMenu = APP_BAUD_RATE_MENU;
                if(selection==1) currentSelectedMenu = APP_COM_PORT_MENU;
                if(selection==2) currentSelectedMenu = APP_CONNECTING_MENU;
                if(selection==3) currentSelectedMenu = APP_DISCONNECTING_MENU;
                selection = 0;
                return true;
    }
    return false;
}

bool Application::ArduinoBaudRateKeyboardHandler()
{
    int keyboardCode = getch();    
    switch (keyboardCode)
    {    
        case KB_UP:
                selection--;
                if(selection<0) selection=12;
                return true;            
    
        case KB_DOWN:
                selection++;
                if(selection>12) selection=0;
                return true;

        case KB_ENTER:
                if(selection==12)
                {
                    currentSelectedMenu = APP_ARDUINO_MENU;
                    selection =0;
                    return true;
                }

                int baudRateIndex = 0;
                for(int baudRate = ArduinoBaudRates::_300; baudRate <= ArduinoBaudRates::_115200; baudRate+=100)
                {
                    if(VerifyBaudRate(baudRate))
                    {
                        int baudRateNumber = static_cast<ArduinoBaudRates>(baudRate);
                        if(selection == baudRateIndex)
                        {
                            arduino.SetBaudRate(baudRateNumber);
                            return true;
                        }
                        baudRateIndex++;
                    }
                }
                return true;
    }
    return false;
}

bool Application::ArduinoComPortKeyboardHandler()
{
    int keyboardCode = getch();

    int AmountOfAvailablePorts = GetAvailableComPorts().size();

    switch (keyboardCode)
    {    
        case KB_UP:
                selection--;
                if(selection<0) selection=AmountOfAvailablePorts;
                return true;            
    
        case KB_DOWN:
                selection++;
                if(selection>AmountOfAvailablePorts) selection=0;
                return true;

        case KB_ENTER:
                if(selection==AmountOfAvailablePorts)
                {
                    currentSelectedMenu = APP_ARDUINO_MENU;
                    selection = 0;
                    return true;
                }

                std::vector<std::wstring> ports = GetAvailableComPorts();

                // Cuz yk, there's no easy way to put a Wstring to a string
                std::string portAsString(ports[selection].begin(), ports[selection].end());
                arduino.SetComPort(portAsString);
                return true;
    }
    return false;
}

bool Application::ArduinoConnectingKeyboardHandler()
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
                if(selection==0)
                {
                    currentSelectedMenu = APP_ARDUINO_MENU;
                    return true;
                }

                if(selection==1)
                {
                    if(!IsComPortListed(arduino.GetComPort()))
                    {
                        selection = 2;
                        return true;
                    }

                    if(arduino.Connect())
                    {
                        selection = 4;
                    }
                    else
                    {
                        selection = 3;
                    }
                    return true;
                }
    }
    return false;
}

bool Application::ArduinoDisconnectingKeyboardHandler()
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
                if(selection==0)
                {
                    currentSelectedMenu = APP_ARDUINO_MENU;
                    return true;
                }

                if(selection==1)
                {
                    if(!IsComPortListed(arduino.GetComPort()))
                    {
                        selection = 2;
                        return true;
                    }

                    if(arduino.Disconnect())
                    {
                        selection = 4;
                    }
                    else
                    {
                        selection = 3;
                    }
                    return true;
                }
    }
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
    system("cls");
	std::cout << "############################################" << std::endl;
    std::cout << "              - Arduino setup -             " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    std::cout << "- Navigate to configure your arduino setup -" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;

    if(selection < 3 && arduino.GetPortState())
    {
        selection = 3;
    }

    auto printBaudRate = [](int baudRate)
    {
        std::cout << "    | ";
        PrintInColour(std::cout, "Current:\t", colors::grey, colors::black);
        PrintInColour(std::cout, std::to_string(baudRate), colors::leaf, colors::black);
        std::cout << "\n";
    };

    auto printComPort = [](std::string comPort)
    {
        std::cout << "    | ";
        PrintInColour(std::cout, "Current:\t", colors::grey, colors::black);
        if(IsComPortListed(comPort))
        {
            PrintInColour(std::cout, comPort, colors::leaf, colors::black);
        }
        else
        {
            PrintInColour(std::cout, comPort, colors::red, colors::black);        
        }
        std::cout << "\n";
    };

    auto printConnectionStatus = [](bool status)
    {
        std::cout << "            | ";
        PrintInColour(std::cout, " Is Connected:\t", colors::grey, colors::black);
        if(status)
        {
            PrintInColour(std::cout, "Yes", colors::green, colors::black);
        }
        else
        {
            PrintInColour(std::cout, "No", colors::red, colors::black); 
        }
        std::cout << "\n";
    };

    auto printCommunicationStatus = [](bool status)
    {
        std::cout << "         | ";
        PrintInColour(std::cout, "Communicates:\t", colors::grey, colors::black);
        if(status)
        {
            PrintInColour(std::cout, "Yes", colors::green, colors::black);
        }
        else
        {
            PrintInColour(std::cout, "No", colors::red, colors::black); 
        }
        std::cout << "\n";
    };

    switch(selection)
    {
        case(0):
            PrintInColour(std::cout, "-> Change Baudrate", colors::aqua, colors::black);
            printBaudRate(arduino.GetBaudRate());
            PrintInColour(std::cout, "   Select Com Port", colors::grey, colors::black);
            printComPort(arduino.GetComPort());
            PrintInColour(std::cout, "   Connect", colors::grey, colors::black);
            printConnectionStatus(arduino.GetPortState());
            PrintInColour(std::cout, "   Disconnect", colors::red, colors::black);
            printCommunicationStatus(arduino.Verify());
            PrintInColour(std::cout, "   Back to main menu", colors::grey, colors::black);
            std::cout << "  ----------------------" << std::endl;
            break;

        case(1):
            PrintInColour(std::cout, "   Change Baudrate", colors::grey, colors::black);
            printBaudRate(arduino.GetBaudRate());
            PrintInColour(std::cout, "-> Select Com Port", colors::aqua, colors::black);
            printComPort(arduino.GetComPort());
            PrintInColour(std::cout, "   Connect", colors::grey, colors::black);
            printConnectionStatus(arduino.GetPortState());
            PrintInColour(std::cout, "   Disconnect", colors::red, colors::black);
            printCommunicationStatus(arduino.Verify());
            PrintInColour(std::cout, "   Back to main menu", colors::grey, colors::black);
            std::cout << "  ----------------------" << std::endl;
            break;

        case(2):
            PrintInColour(std::cout, "   Change Baudrate", colors::grey, colors::black);
            printBaudRate(arduino.GetBaudRate());
            PrintInColour(std::cout, "   Select Com Port", colors::grey, colors::black);
            printComPort(arduino.GetComPort());
            PrintInColour(std::cout, "-> Connect", colors::aqua, colors::black);
            printConnectionStatus(arduino.GetPortState());
            PrintInColour(std::cout, "   Disconnect", colors::red, colors::black);
            printCommunicationStatus(arduino.Verify());
            PrintInColour(std::cout, "   Back to main menu", colors::grey, colors::black);
            std::cout << "  ----------------------" << std::endl;
            break;

        case(3):

            if(arduino.GetPortState())
            {
                PrintInColour(std::cout, "   Change Baudrate", colors::red, colors::black);
                printBaudRate(arduino.GetBaudRate());
                PrintInColour(std::cout, "   Select Com Port", colors::red, colors::black);
                printComPort(arduino.GetComPort());
                PrintInColour(std::cout, "   Connect", colors::red, colors::black);
            }
            else
            {
                PrintInColour(std::cout, "   Change Baudrate", colors::grey, colors::black);
                printBaudRate(arduino.GetBaudRate());
                PrintInColour(std::cout, "   Select Com Port", colors::grey, colors::black);
                printComPort(arduino.GetComPort());
                PrintInColour(std::cout, "   Connect", colors::grey, colors::black);
            }
            printConnectionStatus(arduino.GetPortState());
            PrintInColour(std::cout, "-> Disconnect", colors::aqua, colors::black);
            printCommunicationStatus(arduino.Verify());
            PrintInColour(std::cout, "   Back to main menu", colors::grey, colors::black);
            std::cout << "  ----------------------" << std::endl;
            break;

        case(4):
            if(arduino.GetPortState())
            {
                PrintInColour(std::cout, "   Change Baudrate", colors::red, colors::black);
                printBaudRate(arduino.GetBaudRate());
                PrintInColour(std::cout, "   Select Com Port", colors::red, colors::black);
                printComPort(arduino.GetComPort());
                PrintInColour(std::cout, "   Connect", colors::red, colors::black);
            }
            else
            {
                PrintInColour(std::cout, "   Change Baudrate", colors::grey, colors::black);
                printBaudRate(arduino.GetBaudRate());
                PrintInColour(std::cout, "   Select Com Port", colors::grey, colors::black);
                printComPort(arduino.GetComPort());
                PrintInColour(std::cout, "   Connect", colors::grey, colors::black);
            }
            printConnectionStatus(arduino.GetPortState());

            if(!arduino.GetPortState())
            {
                PrintInColour(std::cout, "   Disconnect", colors::red, colors::black);
            }
            else
            {
                PrintInColour(std::cout, "   Disconnect", colors::grey, colors::black);
            }
            printCommunicationStatus(arduino.Verify());
            PrintInColour(std::cout, "-> Back to main menu", colors::aqua, colors::black);
            std::cout << "  ----------------------" << std::endl;
            break;
    }
    std::cout << "############################################" << std::endl;
    return true;
}

bool Application::DrawArduinoBaudRateMenu()
{
    system("cls");
	std::cout << "############################################" << std::endl;
    std::cout << "              - Arduino setup -             " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    std::cout << "-          Select a new baud rate          -" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;

    auto drawABaudRate = [](int baudrate, bool isSelected, bool isCurrent)
    {
        if(isSelected)
        {
            PrintInColour(std::cout, "-> ", colors::aqua, colors::black);
            std::string result = "";

            if(isCurrent)
            {
                result.append("<");
                result.append(std::to_string(baudrate));
                result.append(">");    
                PrintInColour(std::cout, result, colors::aqua, colors::black);     
            }
            else
            {
                result.append(" ");
                result.append(std::to_string(baudrate));
                PrintInColour(std::cout, result, colors::aqua, colors::black);     
            }
        }
        else
        {
            PrintInColour(std::cout, "   ", colors::aqua, colors::black);
            std::string result = "";

            if(isCurrent)
            {
                result.append("<");
                result.append(std::to_string(baudrate));
                result.append(">");    
                PrintInColour(std::cout, result, colors::lightgrey, colors::black);     
            }
            else
            {
                result.append(" ");
                result.append(std::to_string(baudrate));
                PrintInColour(std::cout, result, colors::grey, colors::black);     
            }
        }
        std::cout << std::endl;
    };

    int baudRateIndex = 0;
    for(int baudRate = ArduinoBaudRates::_300; baudRate <= ArduinoBaudRates::_115200; baudRate+=100)
    {
        if(VerifyBaudRate(baudRate))
        {
            int baudRateNumber = static_cast<ArduinoBaudRates>(baudRate);
            drawABaudRate(baudRateNumber, selection==baudRateIndex, arduino.GetBaudRate()==baudRate);
            baudRateIndex++;
        }
    }
	
    std::cout << "--------------------------------------------" << std::endl;
    
    if(selection==12)
    {
        PrintInColour(std::cout, "->  Confirm\n", colors::leaf, colors::black);
    }
    else
    {
        PrintInColour(std::cout, "    Confirm\n", colors::grey, colors::black);
    }

	std::cout << "############################################" << std::endl;
    return true;
}

bool Application::DrawArduinoComPortMenu()
{
   system("cls");
	std::cout << "############################################" << std::endl;
    std::cout << "              - Arduino setup -             " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    std::cout << "-           Select a new com port          -" << std::endl;
    std::cout << "-        Navigating updates the list       -" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;

    auto drawAComPort = [](std::string comPort, bool isSelected, bool isCurrent)
    {
        if(isSelected)
        {
            PrintInColour(std::cout, "-> ", colors::aqua, colors::black);
            std::string result = "";

            if(isCurrent)
            {
                result.append("<");
                result.append(comPort);
                result.append(">");    
                PrintInColour(std::cout, result, colors::aqua, colors::black);     
            }
            else
            {
                result.append(" ");
                result.append(comPort);
                PrintInColour(std::cout, result, colors::aqua, colors::black);     
            }
        }
        else
        {
            PrintInColour(std::cout, "   ", colors::aqua, colors::black);
            std::string result = "";

            if(isCurrent)
            {
                result.append("<");
                result.append(comPort);
                result.append(">");    
                PrintInColour(std::cout, result, colors::lightgrey, colors::black);     
            }
            else
            {
                result.append(" ");
                result.append(comPort);
                PrintInColour(std::cout, result, colors::grey, colors::black);     
            }
        }
        std::cout << std::endl;
    };

    std::vector<std::wstring> ports = GetAvailableComPorts();
    int amountOfSelections = ports.size();

    if(amountOfSelections == 0)
    {
        PrintInColour(std::cout, "-          NO VALID COM PORTS FOUND        -\n", colors::red, colors::white);
    }

    int baudRateIndex = 0;
    for(int portIndex = 0; portIndex < ports.size(); ++portIndex)
    {
        // Cuz yk, there's no easy way to put a Wstring to a string
        std::string portAsString(ports[portIndex].begin(), ports[portIndex].end());
        drawAComPort(portAsString, selection==portIndex, portAsString==arduino.GetComPort());
    }
	
    std::cout << "--------------------------------------------" << std::endl;
    
    if(selection==amountOfSelections)
    {
        PrintInColour(std::cout, "->  Confirm\n", colors::leaf, colors::black);
    }
    else
    {
        PrintInColour(std::cout, "    Confirm\n", colors::grey, colors::black);
    }

	std::cout << "############################################" << std::endl;
    return true;
}

bool Application::DrawArduinoConnectingMenu()
{
    auto drawConnectionResult = [](int selection)
    {
        switch(selection)
        {
            case(0): std::cout << "-       Go back to the previous menu?      -" << std::endl; break;
            case(1): std::cout << "- Attempt to connect using specified param -" << std::endl; break;
            case(2):
                    PrintInColour(std::cout, "- The COM port isn't listed on your device -\n", colors::black, colors::yellow);
                    break;
            case(3):
                    PrintInColour(std::cout, "- FATAL ERRORS WHILE ATTEMPTING CONNECTION -\n", colors::white, colors::red);
                    break;
            case(4):
                    PrintInColour(std::cout, "-  Com port has been successfully openned  -\n", colors::black, colors::green);
                    break;
        }
    };
    
    auto printBaudRate = [](int baudRate)
    {
        PrintInColour(std::cout, "Baudrate:\t", colors::grey, colors::black);
        PrintInColour(std::cout, std::to_string(baudRate), colors::leaf, colors::black);
        std::cout << "\n";
    };

    auto printComPort = [](std::string comPort)
    {
        PrintInColour(std::cout, "Com port:\t", colors::grey, colors::black);
        if(IsComPortListed(comPort))
        {
            PrintInColour(std::cout, comPort, colors::leaf, colors::black);
        }
        else
        {
            PrintInColour(std::cout, comPort, colors::red, colors::black);        
        }
        std::cout << "\n";
    };

    auto drawButtons = [](int selection)
    {
        std::cout << "         ";
        if(selection==0)
        {
            PrintInColour(std::cout, "[BACK]", colors::white, colors::blue);
        }
        else
        {
            PrintInColour(std::cout, "[BACK]", colors::grey, colors::black);
        }
        std::cout << "         ";
        if(selection==1)
        {
            PrintInColour(std::cout, "[CONNECT]", colors::white, colors::blue);
        }
        else
        {
            PrintInColour(std::cout, "[CONNECT]", colors::grey, colors::black);
        }
        std::cout << std::endl;
    };

    system("cls");
    std::cout << "############################################" << std::endl;
    std::cout << "               - Connection -               " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    drawConnectionResult(selection);
    if(selection>1) selection = 0;
	std::cout << "--------------------------------------------" << std::endl;

    printBaudRate(arduino.GetBaudRate());
    printComPort(arduino.GetComPort());
	std::cout << "--------------------------------------------" << std::endl;
    drawButtons(selection);
    std::cout << "############################################" << std::endl;
    return true;
}

bool Application::DrawArduinoDisconnectingMenu()
{
    auto drawConnectionResult = [](int selection)
    {
        switch(selection)
        {
            case(0): std::cout << "-       Go back to the previous menu?      -" << std::endl; break;
            case(1): std::cout << "-        Disconnect the active port?       -" << std::endl; break;
            case(2):
                    PrintInColour(std::cout, "- The COM port isn't listed on your device -\n", colors::black, colors::yellow);
                    break;
            case(3):
                    PrintInColour(std::cout, "-  FATAL ERROR WHILE TRYING TO DISCONNECT  -\n", colors::white, colors::red);
                    break;
            case(4):
                    PrintInColour(std::cout, "-   Com port has been successfully closed  -\n", colors::black, colors::green);
                    break;
        }
    };
    
    auto printBaudRate = [](int baudRate)
    {
        PrintInColour(std::cout, "Baudrate:\t", colors::grey, colors::black);
        PrintInColour(std::cout, std::to_string(baudRate), colors::leaf, colors::black);
        std::cout << "\n";
    };

    auto printComPort = [](std::string comPort)
    {
        PrintInColour(std::cout, "Com port:\t", colors::grey, colors::black);
        if(IsComPortListed(comPort))
        {
            PrintInColour(std::cout, comPort, colors::leaf, colors::black);
        }
        else
        {
            PrintInColour(std::cout, comPort, colors::red, colors::black);        
        }
        std::cout << "\n";
    };

    auto drawButtons = [](int selection)
    {
        std::cout << "        ";
        if(selection==0)
        {
            PrintInColour(std::cout, "[BACK]", colors::white, colors::blue);
        }
        else
        {
            PrintInColour(std::cout, "[BACK]", colors::grey, colors::black);
        }
        std::cout << "        ";
        if(selection==1)
        {
            PrintInColour(std::cout, "[DISCONNECT]", colors::white, colors::blue);
        }
        else
        {
            PrintInColour(std::cout, "[DISCONNECT]", colors::grey, colors::black);
        }
        std::cout << std::endl;
    };

    system("cls");
    std::cout << "############################################" << std::endl;
    std::cout << "               - Connection -               " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    drawConnectionResult(selection);
    if(selection>1) selection = 0;
	std::cout << "--------------------------------------------" << std::endl;

    printBaudRate(arduino.GetBaudRate());
    printComPort(arduino.GetComPort());
	std::cout << "--------------------------------------------" << std::endl;
    drawButtons(selection);
    std::cout << "############################################" << std::endl;
    return true;
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

    if(!arduino.GetPortState())                     PrintInColour(std::cout, "-      No arduino connected to the PC      -", colors::red, colors::black);
    if(arduino.GetPortState() && !arduino.Verify()) PrintInColour(std::cout, "- Connected devices not answering requests -", colors::black, colors::gold);
    if(arduino.GetPortState() && arduino.Verify())  PrintInColour(std::cout, "-     Connected arduino is operational     -", colors::black, colors::green);
    std::cout << std::endl;

	std::cout << "--------------------------------------------" << std::endl;

    switch(wantedSelectedMenu)
    {
        case(APP_GAME_MENU):
            PrintInColour(std::cout, "   1: Test Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "   2: Arduino setup\n",   colors::grey, colors::black);
            PrintInColour(std::cout, "-> 3: Game Menu\n",       colors::aqua, colors::black);
            PrintInColour(std::cout, "   4: Exit Menu\n",       colors::grey, colors::black);
            break;

        case(APP_TEST_MENU):
            PrintInColour(std::cout, "-> 1: Test Menu\n",       colors::aqua, colors::black);
            PrintInColour(std::cout, "   2: Arduino setup\n",   colors::grey, colors::black);
            PrintInColour(std::cout, "   3: Game Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "   4: Exit Menu\n",       colors::grey, colors::black);
            break;

        case(APP_EXIT_MENU):
            PrintInColour(std::cout, "   1: Test Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "   2: Arduino setup\n",   colors::grey, colors::black);
            PrintInColour(std::cout, "   3: Game Menu\n",       colors::grey, colors::black);
            PrintInColour(std::cout, "-> 4: Exit Menu\n",       colors::red, colors::black);
            break;

        case(APP_ARDUINO_MENU):
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

            case(APP_BAUD_RATE_MENU):
                DrawArduinoBaudRateMenu();
                break;

            case(APP_COM_PORT_MENU):
                DrawArduinoComPortMenu();
                break;

            case(APP_CONNECTING_MENU):
                DrawArduinoConnectingMenu();
                break;

            case(APP_DISCONNECTING_MENU):
                DrawArduinoDisconnectingMenu();
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
    // Allows you to immediately see if a COM port change occurs
    if(oldAmountOfComPorts != GetAvailableComPorts().size())
    {
        oldAmountOfComPorts = GetAvailableComPorts().size();
        requiresNewDrawing = true;
    }

    HandleMenuDrawings();
    HandleKeyboardActions();

    if(frameTimer.TimeLeft() == 0)
    {
        arduino.Update();
        currentGame.Update();
    }
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
        Update();
    }
}