/**
 * @file Utils.hpp
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
#include "Map.h"
#include <iostream>
#include "../JSON/json.hpp"
#include <vector>
#include <fstream>
#include <string>
#include "../Colour/Colour.h"

// - DEFINES - //
#define EM_MAP_WRONG_AMOUNT_OF_PLAYERS  "Invalid specified amount of players"
#define EM_MAP_MAP_VALUE_WRONG_TYPE     "A map value is of the wrong type"
#define EM_MAP_MISSING_MAP_NAME         "Map name info missing from JSON"
#define EM_MAP_MISSING_MAP_SIZEX        "Map X info missing from JSON"
#define EM_MAP_MISSING_MAP_SIZEY        "Map Y info missing from JSON"
#define EM_MAP_MISSING_MAP_AOP          "Map amount of players info missing from JSON"
#define EM_MAP_MISSING_MAP_MAP          "Map array info missing from JSON"
#define EM_MAP_MISSING_MAP_INFO         "Critical map info missing from JSON"
#define EM_MAP_UNDEFINED_ERROR          "UNDEFINED ERROR. PLEASE DEFINE"
#define EM_MAP_CORRUPTED_MAP            "The specified map is corrupted."
#define EM_MAP_NO_JSON_GIVEN            "No JSON was returned from the MAP obj"
#define EM_MAP_MAP_IS_NULLPTR           "The passed map is a nullptr        "
#define EM_MAP_TOO_MANY_PLAYERS         "There is too many players to play  "
#define EM_MAP_NOT_ENOUGH_PLAYERS       "There is not enough players to play"
#define EM_MAP_INVALID_MAP_SIZE         "Specified map sizes are unplayable."
#define EM_MAP_INCORRECT_X_SIZE         "Specified X size does not match real size"
#define EM_MAP_INCORRECT_Y_SIZE         "Specified Y size does not match real size"
#define EM_MAP_NO_ERROR                 "ALL GOOD"
// - FUNCTIONS - //

/**
 * @brief
 * # GetMapError
 * @brief
 * Returns potential errors that can be in a Map
 * JSON. Errors are returned as strings and a
 * full list is available as defines in @ref Utils.hpp
 * @return std::string 
 */
std::string GetMapError(Map* mapObject);

/**
 * @brief
 * # GetMapError
 * @brief
 * Returns potential errors that can be in a Map
 * JSON. Errors are returned as strings and a
 * full list is available as defines in @ref Utils.hpp
 * @return std::string 
 */
std::string GetMapJsonError(nlohmann::json mapJSON);

/**
 * @brief 
 * # VerifyMap
 * @brief
 * Simply returns true or false depending on if the 
 * specified FULL path is a valid path to a JSON
 * BomberMan map. This also calls @ref GetMapError
 * to identify any errors within the JSON as well.
 * @param path 
 * @return true:
 * Map is verified!
 * @return false:
 * Oh oh, errors :(
 */
bool VerifyMap(std::string path);

/**
 * @brief
 * # Check if tile is walkable
 * @brief
 * Returns true if the tile is empty
 * Return false if the tile is not walkable
 * full list is available as defines in @ref Utils.hpp
 * @return bool
 */
bool TileIsWalkable(TileTypes tile);


 /**
  * @brief
  * # Check return the tile position of the player in param
  * @brief
  * return x and y of where
  * Return false if the tile is not walkable
  * full list is available as defines in @ref Utils.hpp
  * @return std::string
  */

get player tile;

std::vector<nlohmann::json> GetAllMaps();
nlohmann::json GetMapJson(std::string path);