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
#include <conio.h>

// - DEFINES - //

// - CLASS - //

ArduinoMenu::ArduinoMenu(AppHandler* currentAppHandler)
{
    appRef = currentAppHandler;
}

/**
 * @brief 
 * Draws the menu that allows the user to select
 * a wanted com port as well as a wanted baud rate
 * and see if their connection was successful or not.
 * @return true 
 * @return false 
 */
bool ArduinoMenu::DrawArduinoMainMenu()
{
    if(oldSelectedSubMenu != selectedSubMenu)
    {
        oldSelectedSubMenu = selectedSubMenu;
        system("cls");
    }
    SetTerminalCursorPosition(0,0);
	std::cout << "############################################" << std::endl;
    std::cout << "              - Arduino setup -             " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    std::cout << "- Navigate to configure your arduino setup -" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;

    if(selection < 3 && appRef->arduinoThread.GetArduino()->GetPortState())
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
            printBaudRate(appRef->arduinoThread.GetArduino()->GetBaudRate());
            PrintInColour(std::cout, "   Select Com Port", colors::grey, colors::black);
            printComPort(appRef->arduinoThread.GetArduino()->GetComPort());
            PrintInColour(std::cout, "   Connect", colors::grey, colors::black);
            printConnectionStatus(appRef->arduinoThread.GetArduino()->GetPortState());
            PrintInColour(std::cout, "   Disconnect", colors::red, colors::black);
            printCommunicationStatus(appRef->arduinoThread.GetArduino()->Verify());
            PrintInColour(std::cout, "   Back to main menu", colors::grey, colors::black);
            std::cout << "  ----------------------" << std::endl;
            break;

        case(1):
            PrintInColour(std::cout, "   Change Baudrate", colors::grey, colors::black);
            printBaudRate(appRef->arduinoThread.GetArduino()->GetBaudRate());
            PrintInColour(std::cout, "-> Select Com Port", colors::aqua, colors::black);
            printComPort(appRef->arduinoThread.GetArduino()->GetComPort());
            PrintInColour(std::cout, "   Connect", colors::grey, colors::black);
            printConnectionStatus(appRef->arduinoThread.GetArduino()->GetPortState());
            PrintInColour(std::cout, "   Disconnect", colors::red, colors::black);
            printCommunicationStatus(appRef->arduinoThread.GetArduino()->Verify());
            PrintInColour(std::cout, "   Back to main menu", colors::grey, colors::black);
            std::cout << "  ----------------------" << std::endl;
            break;

        case(2):
            PrintInColour(std::cout, "   Change Baudrate", colors::grey, colors::black);
            printBaudRate(appRef->arduinoThread.GetArduino()->GetBaudRate());
            PrintInColour(std::cout, "   Select Com Port", colors::grey, colors::black);
            printComPort(appRef->arduinoThread.GetArduino()->GetComPort());
            PrintInColour(std::cout, "-> Connect", colors::aqua, colors::black);
            printConnectionStatus(appRef->arduinoThread.GetArduino()->GetPortState());
            PrintInColour(std::cout, "   Disconnect", colors::red, colors::black);
            printCommunicationStatus(appRef->arduinoThread.GetArduino()->Verify());
            PrintInColour(std::cout, "   Back to main menu", colors::grey, colors::black);
            std::cout << "  ----------------------" << std::endl;
            break;

        case(3):

            if(appRef->arduinoThread.GetArduino()->GetPortState())
            {
                PrintInColour(std::cout, "   Change Baudrate", colors::red, colors::black);
                printBaudRate(appRef->arduinoThread.GetArduino()->GetBaudRate());
                PrintInColour(std::cout, "   Select Com Port", colors::red, colors::black);
                printComPort(appRef->arduinoThread.GetArduino()->GetComPort());
                PrintInColour(std::cout, "   Connect", colors::red, colors::black);
            }
            else
            {
                PrintInColour(std::cout, "   Change Baudrate", colors::grey, colors::black);
                printBaudRate(appRef->arduinoThread.GetArduino()->GetBaudRate());
                PrintInColour(std::cout, "   Select Com Port", colors::grey, colors::black);
                printComPort(appRef->arduinoThread.GetArduino()->GetComPort());
                PrintInColour(std::cout, "   Connect", colors::grey, colors::black);
            }
            printConnectionStatus(appRef->arduinoThread.GetArduino()->GetPortState());
            PrintInColour(std::cout, "-> Disconnect", colors::aqua, colors::black);
            printCommunicationStatus(appRef->arduinoThread.GetArduino()->Verify());
            PrintInColour(std::cout, "   Back to main menu", colors::grey, colors::black);
            std::cout << "  ----------------------" << std::endl;
            break;

        case(4):
            if(appRef->arduinoThread.GetArduino()->GetPortState())
            {
                PrintInColour(std::cout, "   Change Baudrate", colors::red, colors::black);
                printBaudRate(appRef->arduinoThread.GetArduino()->GetBaudRate());
                PrintInColour(std::cout, "   Select Com Port", colors::red, colors::black);
                printComPort(appRef->arduinoThread.GetArduino()->GetComPort());
                PrintInColour(std::cout, "   Connect", colors::red, colors::black);
            }
            else
            {
                PrintInColour(std::cout, "   Change Baudrate", colors::grey, colors::black);
                printBaudRate(appRef->arduinoThread.GetArduino()->GetBaudRate());
                PrintInColour(std::cout, "   Select Com Port", colors::grey, colors::black);
                printComPort(appRef->arduinoThread.GetArduino()->GetComPort());
                PrintInColour(std::cout, "   Connect", colors::grey, colors::black);
            }
            printConnectionStatus(appRef->arduinoThread.GetArduino()->GetPortState());

            if(!appRef->arduinoThread.GetArduino()->GetPortState())
            {
                PrintInColour(std::cout, "   Disconnect", colors::red, colors::black);
            }
            else
            {
                PrintInColour(std::cout, "   Disconnect", colors::grey, colors::black);
            }
            printCommunicationStatus(appRef->arduinoThread.GetArduino()->Verify());
            PrintInColour(std::cout, "-> Back to main menu", colors::aqua, colors::black);
            std::cout << "  ----------------------" << std::endl;
            break;
    }
    std::cout << "############################################" << std::endl;
    return true;
}

bool ArduinoMenu::DrawBaudrateSelectionMenu()
{
    if(oldSelectedSubMenu != selectedSubMenu)
    {
        oldSelectedSubMenu = selectedSubMenu;
        system("cls");
    }
    SetTerminalCursorPosition(0,0);
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
            drawABaudRate(baudRateNumber, selection==baudRateIndex, appRef->arduinoThread.GetArduino()->GetBaudRate()==baudRate);
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

    for(int portIndex = 0; portIndex < ports.size(); ++portIndex)
    {
        // Cuz yk, there's no easy way to put a Wstring to a string
        std::string portAsString(ports[portIndex].begin(), ports[portIndex].end());
        drawAComPort(portAsString, selection==portIndex, portAsString==appRef->arduinoThread.GetArduino()->GetComPort());
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

    if(oldSelectedSubMenu != selectedSubMenu)
    {
        oldSelectedSubMenu = selectedSubMenu;
        system("cls");
    }
    SetTerminalCursorPosition(0,0);
    std::cout << "############################################" << std::endl;
    std::cout << "               - Connection -               " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    drawConnectionResult(selection);
    if(selection>1) selection = 0;
	std::cout << "--------------------------------------------" << std::endl;

    printBaudRate(appRef->arduinoThread.GetArduino()->GetBaudRate());
    printComPort(appRef->arduinoThread.GetArduino()->GetComPort());
	std::cout << "--------------------------------------------" << std::endl;
    drawButtons(selection);
    std::cout << "############################################" << std::endl;
    return true;
}

bool ArduinoMenu::DrawIsConnectingMenu()
{
    system("cls");
    std::cout << "############################################" << std::endl;
    std::cout << "CONNECTING PLEASE WAIT " << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    auto drawConnectionResult = [](int selection)
    {
        switch(selection)
        {
            case(0): std::cout << "-           Nothing  happenned...          -" << std::endl; break;
            case(-1):
                    PrintInColour(std::cout, "- FATAL ERRORS WHILE ATTEMPTING CONNECTION -\n", colors::white, colors::red);
                    break;
            case(1):
                    PrintInColour(std::cout, "-  Com port has been successfully openned  -\n", colors::black, colors::green);
                    break;
        }
    };

    const std::string spinner[] = { 
        "[                                          ]",
        "[#                                         ]",
        "[##                                        ]",
        "[###                                       ]",
        "[ ####                                     ]",
        "[  ####                                    ]",
        "[   ####                                   ]",
        "[    ####                                  ]",
        "[     ####                                 ]",
        "[      ####                                ]",
        "[       ####                               ]",
        "[        ####                              ]",
        "[         ####                             ]",
        "[          ####                            ]",
        "[           ####                           ]",
        "[            ####                          ]",
        "[             ####                         ]",
        "[              ####                        ]",
        "[               ####                       ]",
        "[                ####                      ]",
        "[                 ####                     ]",
        "[                  ####                    ]",
        "[                   ####                   ]",
        "[                    ####                  ]",
        "[                     ####                 ]",
        "[                      ####                ]",
        "[                       ####               ]",
        "[                        ####              ]",
        "[                         ####             ]",
        "[                          ####            ]",
        "[                           ####           ]",
        "[                            ####          ]",
        "[                             ####         ]",
        "[                              ####        ]",
        "[                               ####       ]",
        "[                                ####      ]",
        "[                                 ####     ]",
        "[                                  ####    ]",
        "[                                   ####   ]",
        "[                                    ####  ]",
        "[                                     #### ]",
        "[                                      ####]",
        "[                                       ###]",
        "[                                        ##]",
        "[                                         #]",
                                    };
    int i = 0;
    while(!appRef->arduinoThread.FunctionShouldBeExecuted())
    {
        i++;
        PrintInColour(std::cout, spinner[i % 45], colors::aqua, colors::black);
        std::cout << "\r" << std::flush;
        Sleep(5);
    }

    int result = appRef->arduinoThread.GetFunctionExecutionResult();
    drawConnectionResult(result);
	std::cout << "\r--------------------------------------------" << std::endl;
    std::cout << "PRESS ANYTHING TO GO BACK TO MENUS" << std::endl;
    std::cout << "############################################" << std::endl;

    _getch();
    if(result == 1)
    {
        selectedSubMenu = 0;
        return true;
    }
    selectedSubMenu = APP_CONNECTING_MENU;
    return false;
}

bool ArduinoMenu::DrawDisconnectMenu()
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

    if(oldSelectedSubMenu != selectedSubMenu)
    {
        oldSelectedSubMenu = selectedSubMenu;
        system("cls");
    }
    SetTerminalCursorPosition(0,0);
    std::cout << "############################################" << std::endl;
    std::cout << "               - Connection -               " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
    drawConnectionResult(selection);
    if(selection>1) selection = 0;
	std::cout << "--------------------------------------------" << std::endl;

    printBaudRate(appRef->arduinoThread.GetArduino()->GetBaudRate());
    printComPort(appRef->arduinoThread.GetArduino()->GetComPort());
	std::cout << "--------------------------------------------" << std::endl;
    drawButtons(selection);
    std::cout << "############################################" << std::endl;
    return true;
}



bool ArduinoMenu::HandleKeyboardMainMenu(int keyBoardKey)
{
    // Avoid being able to change baudrate and port when its currently connected.
    if(selection < 3 && appRef->arduinoThread.GetArduino()->GetPortState())
    {
        selection = 3;
    }

    switch (keyBoardKey)
    {    
        case KB_UP:
                selection--;
                if(selection<0) selection=4;

                // Dont hover over Disconnect if it cant be disconnected
                if(selection == 3 && !appRef->arduinoThread.GetArduino()->GetPortState())
                {
                    selection = 2;
                }

                // Avoid being able to change baudrate and port when its currently connected.
                if(selection < 3 && appRef->arduinoThread.GetArduino()->GetPortState())
                {
                    selection = 3;
                }

                return true;            
    
        case KB_DOWN:
                selection++;

                // Dont hover over Disconnect if it cant be disconnected
                if(selection == 3 && !appRef->arduinoThread.GetArduino()->GetPortState())
                {
                    selection = 4;
                }

                if(selection>4) selection=0;
                return true;

        case KB_ESCAPE:
                appRef->currentSelectedMenu = APP_MAIN_MENU;
                selection = 0;
                return true;

        case KB_ENTER:
                if(selection==4) appRef->currentSelectedMenu = APP_MAIN_MENU;
                if(selection==0) selectedSubMenu = APP_BAUD_RATE_MENU;
                if(selection==1) selectedSubMenu = APP_COM_PORT_MENU;
                if(selection==2) selectedSubMenu = APP_CONNECTING_MENU;
                if(selection==3) selectedSubMenu = APP_DISCONNECTING_MENU;
                selection = 0;
                return true;
    }
    return false;
}

bool ArduinoMenu::HandleKeyboardBaudrateMenu(int keyBoardKey)
{
    switch (keyBoardKey)
    {    
        case KB_UP:
                selection--;
                if(selection<0) selection=12;
                return true;            
    
        case KB_DOWN:
                selection++;
                if(selection>12) selection=0;
                return true;

        case KB_ESCAPE:
                selectedSubMenu = APP_MAIN_MENU;
                selection = 0;
                return true;

        case KB_ENTER:
                if(selection==12)
                {
                    selectedSubMenu = APP_MAIN_MENU;
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
                            appRef->arduinoThread.GetArduino()->SetBaudRate(baudRateNumber);
                            return true;
                        }
                        baudRateIndex++;
                    }
                }
                return true;
    }
    return false;
}

bool ArduinoMenu::HandleKeyboardComPortMenu(int keyBoardKey)
{
    int AmountOfAvailablePorts = GetAvailableComPorts().size();

    switch (keyBoardKey)
    {    
        case KB_UP:
                selection--;
                if(selection<0) selection=AmountOfAvailablePorts;
                return true;            
    
        case KB_DOWN:
                selection++;
                if(selection>AmountOfAvailablePorts) selection=0;
                return true;

        case KB_ESCAPE:
                selectedSubMenu = APP_MAIN_MENU;
                selection = 0;
                return true;

        case KB_ENTER:
                if(selection==AmountOfAvailablePorts)
                {
                    selectedSubMenu = APP_MAIN_MENU;
                    selection = 0;
                    return true;
                }

                std::vector<std::wstring> ports = GetAvailableComPorts();

                // Cuz yk, there's no easy way to put a Wstring to a string
                std::string portAsString(ports[selection].begin(), ports[selection].end());
                appRef->arduinoThread.GetArduino()->SetComPort(portAsString);
                return true;
    }
    return false;
}

bool ArduinoMenu::HandleKeyboardConnectMenu(int keyBoardKey)
{
    switch (keyBoardKey)
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

        case KB_ESCAPE:
                selectedSubMenu = APP_MAIN_MENU;
                selection = 0;
                return true;

        case KB_ENTER:
                if(selection==0)
                {
                    selectedSubMenu = APP_MAIN_MENU;
                    return true;
                }

                if(selection==1)
                {
                    if(!IsComPortListed(appRef->arduinoThread.GetArduino()->GetComPort()))
                    {
                        selection = 2;
                        return true;
                    }

                   //if(appRef->arduinoThread.SetExecutionFunction(Functions::startComPort))
                   //{
                   //    selection = 4;
                   //    selectedSubMenu = APP_IS_CONNECTING_MENU;
                   //    return true;
                   //}
                    if(appRef->arduinoThread.GetArduino()->Connect())
                    {
                        selection = 1;
                        selectedSubMenu = APP_MAIN_MENU;
                        return true;
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

bool ArduinoMenu::HandleKeyboardDisconnectMenu(int keyBoardKey)
{
    switch (keyBoardKey)
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

        case KB_ESCAPE:
                selectedSubMenu = APP_MAIN_MENU;
                selection = 0;
                return true;

        case KB_ENTER:
                if(selection==0)
                {
                    selectedSubMenu = APP_MAIN_MENU;
                    return true;
                }

                if(selection==1)
                {
                    if(!IsComPortListed(appRef->arduinoThread.GetArduino()->GetComPort()))
                    {
                        selection = 2;
                        return true;
                    }

                    if(appRef->arduinoThread.GetArduino()->Disconnect())
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
        case(APP_IS_CONNECTING_MENU): DrawIsConnectingMenu(); return true;
    }
    return false;
}

bool ArduinoMenu::OnEnter()
{
    selectedSubMenu = 0;
    oldSelectedSubMenu = -1;
    selection = 0;
    return true;
}

bool ArduinoMenu::OnExit()
{
    selectedSubMenu = 0;
    oldSelectedSubMenu = -1;
    selection = 0;
    return true;
}

bool ArduinoMenu::Update()
{
    return false;
}