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
#include <QtWidgets>

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
#ifndef NDEBUG
    applicationPath.erase(applicationPath.length() - 10, 10);
#else
    applicationPath.erase(applicationPath.length() - 12, 12);
#endif
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
        else
        {
            qFatal() << entry.path().generic_string();
        }
    return allFoundMaps;
}


QPixmap ChangeSVGColor(QString svgName, QColor qcolor)
{
    using namespace std::chrono;
    QFile file(QString::fromStdString(GetSvg(svgName.toStdString())));
    file.open(QIODevice::ReadOnly);
    QByteArray baData = file.readAll();
    QString str = baData;
    str.replace("#000000", qcolor.name());
    baData = str.toUtf8();
    QSvgRenderer svgRenderer(baData);
    QPixmap pix(svgRenderer.defaultSize());
    pix.fill(Qt::transparent);
    QPainter pixPainter(&pix);
    svgRenderer.render(&pixPainter);
    return pix;
}


std::string GetSvg(std::string name)
{
    // Get the path to this application.
    std::string applicationPath = ExePath();

    // Adds the Maps directory to the end of the current path.
#ifndef NDEBUG
    applicationPath.erase(applicationPath.length() - 10, 10);
#else
    applicationPath.erase(applicationPath.length() - 11, 11);
#endif
    applicationPath.append("\\Media\\");
    // Check if directory exists
    if (!std::filesystem::exists(applicationPath))
    {
        return "error";
    }

    // Iterate through all files found in that directory
    applicationPath.append(name);
    applicationPath.append(".svg");
    return applicationPath;
}

std::string GetSvg(TileTypes tile)
{
    std::string name = "";
    switch (tile)
    {
    case(TileTypes::BOMB):                  name = SVG_BOMB; break; 
    case(TileTypes::EMPTY):                 name = SVG_EMPTY; break; 
    case(TileTypes::PERMAWALL):             name = SVG_PERMAWALL; break; 
    case(TileTypes::PLAYER1):               name = SVG_PLAYER1; break; 
    case(TileTypes::PLAYER2):               name = SVG_PLAYER2; break; 
    case(TileTypes::PLAYER3):               name = SVG_PLAYER3; break; 
    case(TileTypes::PLAYER4):               name = SVG_PLAYER4; break; 
    case(TileTypes::PLAYERSPAWN):           name = SVG_PLAYERSPAWN; break; 
    case(TileTypes::POWER_DMG):             name = SVG_POWER_DMG; break; 
    case(TileTypes::POWER_HEART):           name = SVG_POWER_HEART; break;
    case(TileTypes::POWER_MOREBOMB):        name = SVG_POWER_MOREBOMB; break;
    case(TileTypes::POWER_REACH):           name = SVG_POWER_REACH; break;
    case(TileTypes::POWER_SPEED):           name = SVG_POWER_SPEED; break;
    case(TileTypes::POWER_BOMB_OF_WALLS):   name = SVG_POWER_BOMB_OF_WALLS; break;
    case(TileTypes::POWER_DEPLOYABLE_WALL): name = SVG_POWER_DEPLOYABLE_WALL; break;
    case(TileTypes::SMOKE):                 name = SVG_SMOKE; break;
    case(TileTypes::SMOKE1):                name = SVG_SMOKE1; break;
    case(TileTypes::SMOKE2):                name = SVG_SMOKE2; break;
    case(TileTypes::SMOKE3):                name = SVG_SMOKE3; break;
    case(TileTypes::SMOKE4):                name = SVG_SMOKE4; break;
    case(TileTypes::SMOKE5):                name = SVG_SMOKE5; break;
    case(TileTypes::WALL):                  name = SVG_WALL; break;
    }
    return GetSvg(name);
}

bool VerifyMap(std::string path)
{
    // Check if the file exists.
    if(!std::filesystem::exists(path))
    {
        qFatal() << QString::fromStdString(path) << ": path does not exist";
        return false;
    }

    auto directoryEntry = std::filesystem::directory_entry(path);

    if(directoryEntry.path().extension() != ".json")
    {
        qFatal() << QString::fromStdString(path) << ": missing .json";
        std::cout << directoryEntry.path().extension() << std::endl;
        return false;
    }

    // Get the json at that location (yet to know if its good or nah)
    nlohmann::json fileContent = GetMapJson(path);

    if(fileContent.is_discarded())
    {
        qFatal() << QString::fromStdString(path) << ": invalid JSON file";

        // Invalid JSON file. There's errors n shit innit bruh
        return false;
    }

    return true;
}

bool TileIsWalkable(TileTypes tile)
{
    switch (tile)
    {
        case TileTypes::PERMAWALL:
        case TileTypes::WALL:
            return false;
            break;
    }
    return true;
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
        case(TileTypes::POWER_BOMB_OF_WALLS):           std::cout << "POWER_BOMB_OF_WALLS   "; return;
        case(TileTypes::POWER_DEPLOYABLE_WALL):         std::cout << "POWER_DEPLOYABLE_WALL   "; return;
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
    case TileTypes::POWER_REACH:    return PowerUpID::explosion_radius_increase;
    case TileTypes::POWER_SPEED:    return PowerUpID::speed_increase;
    case TileTypes::POWER_DEPLOYABLE_WALL:    return PowerUpID::deployableWall;
    case TileTypes::POWER_BOMB_OF_WALLS:    return PowerUpID::bombWall;
    default:                        return -1;
    }
}

TileTypes GetTileFromPowerUp(int powerUpID)
{
    switch (powerUpID)
    {
        case(PowerUpID::damage_increase):           return TileTypes::POWER_DMG;
        case(PowerUpID::health_increase):           return TileTypes::POWER_HEART;
        case(PowerUpID::nb_bomb_increase):          return TileTypes::POWER_MOREBOMB;
        case(PowerUpID::explosion_radius_increase): return TileTypes::POWER_REACH;
        case(PowerUpID::speed_increase):            return TileTypes::POWER_SPEED;
        case(PowerUpID::bombWall):                  return TileTypes::POWER_BOMB_OF_WALLS;
        case(PowerUpID::deployableWall):            return TileTypes::POWER_DEPLOYABLE_WALL;
        default:   return TileTypes::EMPTY;
    }
}

bool TileIsSmoke(TileTypes tile)
{
    switch (tile)
    {
        case TileTypes::SMOKE:
        case TileTypes::SMOKE1:
        case TileTypes::SMOKE2:
        case TileTypes::SMOKE3:
        case TileTypes::SMOKE4:
        case TileTypes::SMOKE5:
            return true;
            break;
    }
    return false;
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