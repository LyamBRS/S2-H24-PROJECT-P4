/**
 * @file ArduinoMenu.cpp
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
#include "ArduinoMenu.h"

// - DEFINES - //

// - CLASS - //
bool ArduinoMenu::DrawArduinoMainMenu()
{
    system("cls");
	std::cout << "############################################" << std::endl;
    std::cout << "              - Arduino setup -             " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    std::cout << "- Navigate to configure your arduino setup -" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;

    if(selection < 3 && appRef->arduino.GetPortState())
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
            printBaudRate(appRef->arduino.GetBaudRate());
            PrintInColour(std::cout, "   Select Com Port", colors::grey, colors::black);
            printComPort(appRef->arduino.GetComPort());
            PrintInColour(std::cout, "   Connect", colors::grey, colors::black);
            printConnectionStatus(appRef->arduino.GetPortState());
            PrintInColour(std::cout, "   Disconnect", colors::red, colors::black);
            printCommunicationStatus(appRef->arduino.Verify());
            PrintInColour(std::cout, "   Back to main menu", colors::grey, colors::black);
            std::cout << "  ----------------------" << std::endl;
            break;

        case(1):
            PrintInColour(std::cout, "   Change Baudrate", colors::grey, colors::black);
            printBaudRate(appRef->arduino.GetBaudRate());
            PrintInColour(std::cout, "-> Select Com Port", colors::aqua, colors::black);
            printComPort(appRef->arduino.GetComPort());
            PrintInColour(std::cout, "   Connect", colors::grey, colors::black);
            printConnectionStatus(appRef->arduino.GetPortState());
            PrintInColour(std::cout, "   Disconnect", colors::red, colors::black);
            printCommunicationStatus(appRef->arduino.Verify());
            PrintInColour(std::cout, "   Back to main menu", colors::grey, colors::black);
            std::cout << "  ----------------------" << std::endl;
            break;

        case(2):
            PrintInColour(std::cout, "   Change Baudrate", colors::grey, colors::black);
            printBaudRate(appRef->arduino.GetBaudRate());
            PrintInColour(std::cout, "   Select Com Port", colors::grey, colors::black);
            printComPort(appRef->arduino.GetComPort());
            PrintInColour(std::cout, "-> Connect", colors::aqua, colors::black);
            printConnectionStatus(appRef->arduino.GetPortState());
            PrintInColour(std::cout, "   Disconnect", colors::red, colors::black);
            printCommunicationStatus(appRef->arduino.Verify());
            PrintInColour(std::cout, "   Back to main menu", colors::grey, colors::black);
            std::cout << "  ----------------------" << std::endl;
            break;

        case(3):

            if(appRef->arduino.GetPortState())
            {
                PrintInColour(std::cout, "   Change Baudrate", colors::red, colors::black);
                printBaudRate(appRef->arduino.GetBaudRate());
                PrintInColour(std::cout, "   Select Com Port", colors::red, colors::black);
                printComPort(appRef->arduino.GetComPort());
                PrintInColour(std::cout, "   Connect", colors::red, colors::black);
            }
            else
            {
                PrintInColour(std::cout, "   Change Baudrate", colors::grey, colors::black);
                printBaudRate(appRef->arduino.GetBaudRate());
                PrintInColour(std::cout, "   Select Com Port", colors::grey, colors::black);
                printComPort(appRef->arduino.GetComPort());
                PrintInColour(std::cout, "   Connect", colors::grey, colors::black);
            }
            printConnectionStatus(appRef->arduino.GetPortState());
            PrintInColour(std::cout, "-> Disconnect", colors::aqua, colors::black);
            printCommunicationStatus(appRef->arduino.Verify());
            PrintInColour(std::cout, "   Back to main menu", colors::grey, colors::black);
            std::cout << "  ----------------------" << std::endl;
            break;

        case(4):
            if(appRef->arduino.GetPortState())
            {
                PrintInColour(std::cout, "   Change Baudrate", colors::red, colors::black);
                printBaudRate(appRef->arduino.GetBaudRate());
                PrintInColour(std::cout, "   Select Com Port", colors::red, colors::black);
                printComPort(appRef->arduino.GetComPort());
                PrintInColour(std::cout, "   Connect", colors::red, colors::black);
            }
            else
            {
                PrintInColour(std::cout, "   Change Baudrate", colors::grey, colors::black);
                printBaudRate(appRef->arduino.GetBaudRate());
                PrintInColour(std::cout, "   Select Com Port", colors::grey, colors::black);
                printComPort(appRef->arduino.GetComPort());
                PrintInColour(std::cout, "   Connect", colors::grey, colors::black);
            }
            printConnectionStatus(appRef->arduino.GetPortState());

            if(!appRef->arduino.GetPortState())
            {
                PrintInColour(std::cout, "   Disconnect", colors::red, colors::black);
            }
            else
            {
                PrintInColour(std::cout, "   Disconnect", colors::grey, colors::black);
            }
            printCommunicationStatus(appRef->arduino.Verify());
            PrintInColour(std::cout, "-> Back to main menu", colors::aqua, colors::black);
            std::cout << "  ----------------------" << std::endl;
            break;
    }
    std::cout << "############################################" << std::endl;
    return true;
}

bool ArduinoMenu::DrawBaudrateSelectionMenu()
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
            drawABaudRate(baudRateNumber, selection==baudRateIndex, appRef->arduino.GetBaudRate()==baudRate);
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

bool ArduinoMenu::DrawComPortSelectionMenu()
{
    return false;
}

bool ArduinoMenu::DrawConnectMenu()
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

    printBaudRate(appRef->arduino.GetBaudRate());
    printComPort(appRef->arduino.GetComPort());
	std::cout << "--------------------------------------------" << std::endl;
    drawButtons(selection);
    std::cout << "############################################" << std::endl;
    return true;
}

bool ArduinoMenu::DrawDisconnectMenu()
{
}

bool ArduinoMenu::HandleKeyboardMainMenu()
{
    return false;
}

bool ArduinoMenu::HandleKeyboardBaudrateMenu()
{
    return false;
}

bool ArduinoMenu::HandleKeyboardComPortMenu()
{
    return false;
}

bool ArduinoMenu::HandleKeyboardConnectMenu()
{
    return false;
}

bool ArduinoMenu::HandleKeyboardDisconnectMenu()
{
    return false;
}





bool ArduinoMenu::HandleKeyboard(int keyBoardKey)
{
    switch(selectedSubMenu)
    {
        case(0): return(HandleKeyboardMainMenu(keyBoardKey));
        case(1): return(HandleKeyboardBaudrateMenu(keyBoardKey));
        case(2): return(HandleKeyboardComPortMenu(keyBoardKey));
        case(3): return(HandleKeyboardConnectMenu(keyBoardKey));
        case(4): return(HandleKeyboardDisconnectMenu(keyBoardKey));
    }
    return false; 
}

bool ArduinoMenu::Draw()
{
    switch(selectedSubMenu)
    {
        case(0): DrawArduinoMainMenu(); return true;
        case(1): DrawBaudrateSelectionMenu(); return true;
        case(2): DrawComPortSelectionMenu(); return true;
        case(3): DrawConnectMenu(); return true;
        case(4): DrawDisconnectMenu(); return true;
    }
    return false;
}

bool ArduinoMenu::OnEnter()
{
    selectedSubMenu = 0;
    selection = 0;
    return true;
}

bool ArduinoMenu::OnExit()
{
    selectedSubMenu = 0;
    selection = 0;
    return true;
}