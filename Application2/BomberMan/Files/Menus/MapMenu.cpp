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

cMapMenu::cMapMenu(AppHandler* currentAppHandler)
{
    appRef = currentAppHandler;
}

bool cMapMenu::HandleKeyboard(int keyBoardKey)
{
    switch (keyBoardKey)
    {    
        case KB_RIGHT:
                SelectionPrevious();
                return true;            
    
        case KB_LEFT:
                SelectionNext();
                return true;                  

        case KB_ESCAPE:
                appRef->currentSelectedMenu = APP_MAIN_MENU;
                setSelection(0);
                return true;

        case KB_ENTER:
                appRef->currentSelectedMenu = APP_GAME_MENU;
                appRef->wantedMapIndex = selection;
                return true;
    }
    return false;
}

bool cMapMenu::Draw()
{
    std::vector<nlohmann::json> allMaps = GetAllMaps();
    amountOfMaps = (int)allMaps.size();
    
    ResizeTerminal(100, 100);
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
        setSelection(0);
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

    std::string result = "< ";
    result.append(std::to_string(selection+1));
    result.append(" // ");
    result.append(std::to_string(amountOfMaps));
    result.append(" >");

    bool flip = false;
    while(result.size() < 16)
    {
        flip = !flip;
        if(flip)
        {
            result.insert(0, " ");
        }
        else
        {
            result.append(" ");       
        }
    }
    appRef->SetMessage(result);

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

    map->Draw();

    std::cout << "############################################" << std::endl;
    return true;
}

bool cMapMenu::OnEnter()
{
    appRef->wantedMapIndex = 0;
    setSelection(0);
    return true;
}

bool cMapMenu::OnExit()
{
    setSelection(0);
    return true;
}

bool cMapMenu::OnMapSelect() 
{
    std::vector<nlohmann::json> allMaps = GetAllMaps();

    // Corruption detection
    if (GetMapJsonError(allMaps[selection]) != EM_MAP_NO_ERROR)
    {
        return false;
    }

    map = new Map(allMaps[selection]);
    return true;
}

bool cMapMenu::Update()
{
    return false;
}

void cMapMenu::setSelection(int selected) {
    selection = selected;
    OnMapSelect();
}

void cMapMenu::SelectionNext() {
    selection++;
    if (selection > amountOfMaps - 1) selection = 0;
    OnMapSelect();
}

void cMapMenu::SelectionPrevious() {
    selection--;
    if (selection < 0) selection = amountOfMaps - 1;
    if (selection < 0) selection = 0;
    OnMapSelect();
}