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
std::vector<nlohmann::json> GetAllMaps()
{
    std::vector<nlohmann::json> allFoundMaps;

    // Get the path to this application.
    std::string applicationPath = ExePath();

    // Adds the Maps directory to the end of the current path.
    applicationPath.append("\\Maps\\");
    // std::cout << applicationPath << std::endl;
    // std::cout << std::endl;

    // Check if directory exists
    if(!std::filesystem::exists(applicationPath))
    {
        return allFoundMaps;
    }

    // Iterate through all files found in that directory
    for (const auto & entry : std::filesystem::directory_iterator(applicationPath))
        if(VerifyMap(entry.path().generic_string()))
        {
            allFoundMaps.push_back(GetMapJson(entry.path().generic_string()));
        }
    return allFoundMaps;
}

bool VerifyMap(std::string path)
{
    // Check if the file exists.
    if(!std::filesystem::exists(path))
    {
        return false;
    }

    auto directoryEntry = std::filesystem::directory_entry(path);

    if(directoryEntry.path().extension() != ".json")
    {
        std::cout << directoryEntry.path().extension() << std::endl;
        return false;
    }

    // Get the json at that location (yet to know if its good or nah)
    nlohmann::json fileContent = GetMapJson(path);

    if(fileContent.is_discarded())
    {
        // Invalid JSON file. There's errors n shit innit bruh
        return false;
    }

    return true;
}

nlohmann::json GetMapJson(std::string path)
{
    // Open the file
    std::ifstream inputFile(path);
    nlohmann::json fileContent;

    // Check if the file is successfully opened
    if (inputFile.is_open()) {
        // Read the content into a string
        std::string fileContent(
            (std::istreambuf_iterator<char>(inputFile)),
            (std::istreambuf_iterator<char>())
        );

        // Close the file
        inputFile.close();

        nlohmann::json jsonContents = nlohmann::json::parse(fileContent, nullptr, false);
        return jsonContents;

        // Display the content
        //std::cout << "File content:\n" << fileContent << std::endl;
    } else {
        std::cerr << "Unable to open file: " << path << std::endl;
        return fileContent;
    }

    return fileContent;
}

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

    PrintInColour(std::cout, "-                ",           colors::white, colors::darkpurple);
    PrintInColour(std::cout, "< ",                          colors::white, colors::darkpurple);
    PrintInColour(std::cout, std::to_string(selection+1),   colors::white, colors::darkpurple);
    PrintInColour(std::cout, " // ",                         colors::white, colors::darkpurple);
    PrintInColour(std::cout, std::to_string(amountOfMaps),  colors::white, colors::darkpurple);
    PrintInColour(std::cout, " >                -\n",       colors::white, colors::darkpurple);
    // PRINT NAVIGATION BAR
    std::cout << std::endl;


    // - WHERE TO DO DA LIL MAP PREVIEW :D - //

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

bool MapMenu::Update()
{
    return false;
}