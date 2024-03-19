/**
 * @file Utils.cpp
 * @author LyamBRS
 * @brief
 * File containing functions used to run simple
 * or in depth verifications of MAP objects and
 * or JSON objects containing MAP informations.
 * @version 0.1
 * @date 2024-03-09
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "Utils.hpp"


// - PROGRAM - //


bool checkIfTileIsPlayer(TileTypes tile)
{
    if (tile == TileTypes::PLAYER1 || tile == TileTypes::PLAYER2 ||
        tile == TileTypes::PLAYER3 || tile == TileTypes::PLAYER4) {
        return true;
    }
    return false;
}

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

bool TileIsWalkable(TileTypes tile)
{
    switch (tile)
    {
    case TileTypes::EMPTY:
        return true;
        break;
    case TileTypes::PERMAWALL:
        return false;
        break;
    case TileTypes::WALL:
        return false;
        break;
    case TileTypes::PLAYERSPAWN:
        return true;
        break;
    case TileTypes::PLAYER1:
        return true;
        break;
    case TileTypes::PLAYER2:
        return true;
        break;
    case TileTypes::PLAYER3:
        return true;
        break;
    case TileTypes::PLAYER4:
        return true;
        break;
    case TileTypes::BOMB:
        return true;
        break;
    case TileTypes::SMOKE:
        return true;
        break;
    case TileTypes::POWER_DMG:
        return true;
    case TileTypes::POWER_HEART:
        return true;
    case TileTypes::POWER_MOREBOMB:
        return true;
    case TileTypes::POWER_REACH:
        return true;
    case TileTypes::POWER_SPEED:
        return true;
        break;
    default:
        return false;
        break;
    }
}

void PrintTileName(TileTypes tile)
{
    switch(tile)
    {
        case(TileTypes::BOMB):              std::cout << "BOMB          "; return;
        case(TileTypes::EMPTY):             std::cout << "EMPTY         "; return;
        case(TileTypes::PERMAWALL):         std::cout << "PERMAWALL     "; return;
        case(TileTypes::PLAYER1):           std::cout << "PLAYER1       "; return;
        case(TileTypes::PLAYER2):           std::cout << "PLAYER2       "; return;
        case(TileTypes::PLAYER3):           std::cout << "PLAYER3       "; return;
        case(TileTypes::PLAYER4):           std::cout << "PLAYER4       "; return;
        case(TileTypes::PLAYERSPAWN):       std::cout << "PLAYERSPAWN   "; return;
        case(TileTypes::POWER_DMG):         std::cout << "POWER_DMG     "; return;
        case(TileTypes::POWER_HEART):       std::cout << "POWER_HEART   "; return;
        case(TileTypes::POWER_MOREBOMB):    std::cout << "POWER_MOREBOMB"; return;
        case(TileTypes::POWER_REACH):       std::cout << "POWER_REACH   "; return;
        case(TileTypes::POWER_SPEED):       std::cout << "POWER_SPEED   "; return;
        case(TileTypes::SMOKE):             std::cout << "SMOKE         "; return;
        case(TileTypes::WALL):              std::cout << "WALL          "; return;
    }
    std::cout << "UNKNOWN       ";
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

int GetPowerUpFromTile(TileTypes tile)
{
    switch (tile)
    {
    case TileTypes::EMPTY:          return -1;
    case TileTypes::PERMAWALL:      return -1;
    case TileTypes::WALL:           return -1;
    case TileTypes::PLAYERSPAWN:    return -1;
    case TileTypes::PLAYER1:        return -1;
    case TileTypes::PLAYER2:        return -1;
    case TileTypes::PLAYER3:        return -1;
    case TileTypes::PLAYER4:        return -1;
    case TileTypes::BOMB:           return -1;
    case TileTypes::SMOKE:          return -1;
    case TileTypes::POWER_DMG:      return PowerUpID::damage_increase;
    case TileTypes::POWER_HEART:    return PowerUpID::health_increase;
    case TileTypes::POWER_MOREBOMB: return PowerUpID::nb_bomb_increase;
    case TileTypes::POWER_REACH:    return PowerUpID::powerUpFName;
    case TileTypes::POWER_SPEED:    return PowerUpID::speed_increase;
    default:                        return -1;
    }
}

TileTypes GetTileFromPowerUp(int powerUpID)
{
    SetTerminalCursorPosition(0,0);
    std::cout << powerUpID << std::endl;
    switch (powerUpID)
    {
        case(PowerUpID::damage_increase):   return TileTypes::POWER_DMG;
        case(PowerUpID::health_increase):   return TileTypes::POWER_HEART;
        case(PowerUpID::nb_bomb_increase):  return TileTypes::POWER_MOREBOMB;
        case(PowerUpID::powerUpFName):      return TileTypes::POWER_REACH;
        case(PowerUpID::speed_increase):    return TileTypes::POWER_SPEED;
        default:   return TileTypes::EMPTY;
    }
}

/**
 * @brief
 * # GetMapError
 * @brief
 * Returns potential errors that can be in a Map
 * JSON. Errors are returned as strings and a
 * full list is available as defines in @ref Utils.hpp
 * @return std::string 
 */
std::string GetMapError(Map* mapObject)
{
    //return GetMapJsonError(*mapObject->GetCurrentMap());
    return "";
}

std::string GetMapJsonError(nlohmann::json mapJSON)
{
    try
    {
        // Check if any JSON was returned.
        if(mapJSON == nullptr)  {return EM_MAP_NO_JSON_GIVEN;}
    
        // Check if the overall JSON is corrupted or not.
        if(mapJSON.is_discarded())  {return EM_MAP_CORRUPTED_MAP;}

        // Check if all the needed attributes exists in that JSON file.
        if(mapJSON.find("name")             == mapJSON.end())    {return EM_MAP_MISSING_MAP_NAME;}
        if(mapJSON.find("sizeX")            == mapJSON.end())    {return EM_MAP_MISSING_MAP_SIZEX;}
        if(mapJSON.find("sizeY")            == mapJSON.end())    {return EM_MAP_MISSING_MAP_SIZEY;}
        if(mapJSON.find("amountOfPlayers")  == mapJSON.end())    {return EM_MAP_MISSING_MAP_AOP;}
        if(mapJSON.find("map")              == mapJSON.end())    {return EM_MAP_MISSING_MAP_MAP;}

        if(mapJSON["name"].is_null())               {return EM_MAP_MISSING_MAP_NAME;}
        if(mapJSON["sizeX"].is_null())              {return EM_MAP_MISSING_MAP_SIZEX;}
        if(mapJSON["sizeY"].is_null())              {return EM_MAP_MISSING_MAP_SIZEY;}
        if(mapJSON["amountOfPlayers"].is_null())    {return EM_MAP_MISSING_MAP_AOP;}
        if(mapJSON["map"].is_null())                {return EM_MAP_MISSING_MAP_MAP;}

        // - Check if the attributes presented are of the right type.
        auto& amountOfPlayers = mapJSON["amountOfPlayers"];
        auto& name = mapJSON["name"];
        auto& sizeX = mapJSON["sizeX"];
        auto& sizeY = mapJSON["sizeY"];
        auto& mapArray = mapJSON["map"];

        if(!amountOfPlayers.is_number_integer())    {return EM_MAP_MAP_VALUE_WRONG_TYPE;}
        if(!name.is_string())                       {return EM_MAP_MAP_VALUE_WRONG_TYPE; }
        if(!sizeX.is_number_integer())              {return EM_MAP_MAP_VALUE_WRONG_TYPE; }
        if(!sizeY.is_number_integer())              {return EM_MAP_MAP_VALUE_WRONG_TYPE;}
        if(!mapArray.is_array())                    {return EM_MAP_MAP_VALUE_WRONG_TYPE;}


        // - Check if the values are valid.
        if(mapJSON["amountOfPlayers"] < 2)   {return EM_MAP_WRONG_AMOUNT_OF_PLAYERS;}
        if(mapJSON["sizeX"] < 5)             {return EM_MAP_INVALID_MAP_SIZE;}
        if(mapJSON["sizeY"] < 5)             {return EM_MAP_INVALID_MAP_SIZE;}
        if(mapJSON["sizeX"] > 99)            {return EM_MAP_INVALID_MAP_SIZE;}
        if(mapJSON["sizeY"] > 99)            {return EM_MAP_INVALID_MAP_SIZE;}

        // Checking if MAP sizes actually corresponds to specified sizes.
        if(mapArray.size() != mapJSON["sizeY"])  {return EM_MAP_INCORRECT_Y_SIZE;}

        // Checks, but for X axis ong ong
        for (const auto& row : mapArray) {
            if (!row.is_array() || row.size() != mapJSON["sizeX"]) {
                return EM_MAP_INCORRECT_Y_SIZE;
            }
        }
    }
    catch(const nlohmann::json::exception& e)
    {
        //std::cerr << e.what() << '\n';
        return EM_MAP_CORRUPTED_MAP;
    }
    return EM_MAP_NO_ERROR;
}