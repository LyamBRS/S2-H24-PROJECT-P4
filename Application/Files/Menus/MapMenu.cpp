/**
 * @file MapMenu.cpp
 * @author LyamBRS
 * @brief
 * Header definition of the ExitMenu class
 * which allows a ExitMenu to be handled.
 * @version 0.1
 * @date 2024-02-15
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "MapMenu.h"

// - DEFINES - //


// - FUNCTIONS - //

// - CLASS - //

MapMenu::MapMenu(AppHandler* currentAppHandler)
{
    appRef = currentAppHandler;
}

bool MapMenu::HandleKeyboard(int keyBoardKey)
{
    switch (keyBoardKey)
    {    
        case KB_RIGHT:
                selection--;
                if(selection<0) selection=amountOfMaps-1;
                if(selection<0) selection = 0;
                return true;            
    
        case KB_LEFT:
                selection++;
                if(selection>amountOfMaps-1) selection=0;
                return true;                  

        case KB_ESCAPE:
                appRef->currentSelectedMenu = 0;
                selection = 0;
                return true;

        case KB_ENTER:
               // OnMapSelect();
                return true;
    }
    return false;
}

bool MapMenu::Draw()
{
    std::vector<nlohmann::json> allMaps = GetAllMaps();
    amountOfMaps = allMaps.size();

    system("cls");
	std::cout << "############################################" << std::endl;
    std::cout << "              - Map selection -             " << std::endl;
	std::cout << "--------------------------------------------" << std::endl;

    // NO MAPS WERE FOUND... ROH OH. (Copy the map folder into your debug folder that Visual Studio generates. ;D)
    if(allMaps.size() == 0)
    {
        PrintInColour(std::cout, "! ERROR: No maps were found on your device !\n", colors::white, colors::red);
        PrintInColour(std::cout, "!  Make sure you have a Maps folder where  !\n", colors::white, colors::red);
        PrintInColour(std::cout, "!         your application .exe is         !\n", colors::white, colors::red);
        std::cout << "--------------------------------------------" << std::endl;
        PrintInColour(std::cout, "- Path to the Maps folder: ", colors::gold, colors::black);
        std::cout << ExePath().append("\\Maps\\") << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "                    ";
        PrintInColour(std::cout, "[OK]", colors::white, colors::electric);
        std::cout << "                    " << std::endl;
        selection = 0;
        std::cout << "############################################" << std::endl;
        return false;
    }

    std::cout << "- Press left/right to change selected map  -" << std::endl;
    std::cout << "-      Press enter to  start the game      -" << std::endl;
    std::cout << "-       Press esc to leave this menu       -" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;

    // std::cout << "- Controller status: | -" << std::endl;
    // std::cout << "- Connected players: | -" << std::endl;
	// std::cout << "--------------------------------------------" << std::endl;
    // std::cout << "- Name:              | -" << std::endl;
    // std::cout << "- Sizes:             | -" << std::endl;
    // std::cout << "- Max players:       | -" << std::endl;
	// std::cout << "--------------------------------------------" << std::endl;
	// std::cout << "-                < x // y >                -" << std::endl;

    // PRINT CONTROLLER STATS

    std::cout << selection << std::endl;
    PrintInColour(std::cout, "- Controller status: ", colors::grey, colors::black);
    std::cout << "| ";
    if(!appRef->arduinoThread.GetArduino()->GetPortState())
    {
        PrintInColour(std::cout, "DISCONNECTED\n", colors::red, colors::black);
    }
    else
    {
        if(appRef->arduinoThread.GetArduino()->Verify())
        {
            PrintInColour(std::cout, "CONNECTED\n", colors::leaf, colors::black);
        }
        else
        {
            PrintInColour(std::cout, "UNRESPONSIVE\n", colors::gold, colors::black);
        }
    }

    PrintInColour(std::cout, "- Connected players: ", colors::grey, colors::black);
    std::cout << "| ";
    if(!appRef->arduinoThread.GetArduino()->GetPortState())
    {
        PrintInColour(std::cout, "0", colors::red, colors::black);
    }
    else
    {
        if(appRef->arduinoThread.GetArduino()->Verify())
        {
            PrintInColour(std::cout, std::to_string(appRef->arduinoThread.GetArduino()->AmountOfConnectedPlayers()), colors::leaf, colors::black);
        }
        else
        {
            PrintInColour(std::cout, "0", colors::gold, colors::black);
        }
    }
    std::cout << std::endl;

    PrintInColour(std::cout, "-                ",           colors::white, colors::darkpurple);
    PrintInColour(std::cout, "< ",                          colors::white, colors::darkpurple);
    PrintInColour(std::cout, std::to_string(selection+1),   colors::white, colors::darkpurple);
    PrintInColour(std::cout, " // ",                         colors::white, colors::darkpurple);
    PrintInColour(std::cout, std::to_string(amountOfMaps),  colors::white, colors::darkpurple);
    PrintInColour(std::cout, " >                -\n",       colors::white, colors::darkpurple);

    // VERIFY THE MAP PRIOR TO PULLING ITS DATA
    std::string error = GetMapJsonError(allMaps[selection]);
    if(error != EM_MAP_NO_ERROR)
    {
        PrintInColour(std::cout, "-           MAP CORRUPTION FOUND           -\n", colors::white, colors::red);
        std::cout <<             "--------------------------------------------" << std::endl;
        PrintInColour(std::cout, error, colors::lightred, colors::black);
        std::cout << "\n############################################" << std::endl;
        return false;
    }


    // PRINT MAP STATS
    PrintInColour(std::cout, "- Name:              ", colors::grey, colors::black);
    std::cout << "| ";
    PrintInColour(std::cout, allMaps[selection]["name"], colors::aqua, colors::black);
    std::cout << std::endl;

    int sizeX = allMaps[selection]["sizeX"];
    int sizeY = allMaps[selection]["sizeY"];
    int amountOfPlayers = allMaps[selection]["amountOfPlayers"];

    PrintInColour(std::cout, "- Sizes:             ", colors::grey, colors::black);
    std::cout << "| ";
    PrintInColour(std::cout, std::to_string(sizeX), colors::aqua, colors::black);
    std::cout << " by ";
    PrintInColour(std::cout, std::to_string(sizeY), colors::aqua, colors::black);
    std::cout << std::endl;

    PrintInColour(std::cout, "- Max players:       ", colors::grey, colors::black);
    std::cout << "| ";
    PrintInColour(std::cout, std::to_string(amountOfPlayers), colors::aqua, colors::black);
    std::cout << std::endl;
    // PRINT NAVIGATION BAR
    std::cout << std::endl;

    OnMapSelect();

    std::cout << "############################################" << std::endl;
    return true;
}

bool MapMenu::OnEnter()
{
    selection = 0;
    return false;
}

bool MapMenu::OnExit()
{
    selection = 0;
    return false;
}

bool MapMenu::OnMapSelect() 
{
    std::vector<nlohmann::json> allMaps = GetAllMaps();
    map = new Map(allMaps[selection]);
    map->Draw();
    return true;
}

bool MapMenu::Update()
{
    return false;
}