/**
 * @file Map.h
 * @author LyamBRS
 * @brief
 * Contains the header definition for the map
 * class which allows the handling of a map
 * in the application. Does what a map do
 * ong fr fr (see class definition ;D)
 * @version 0.1
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include <iostream>
#include "../JSON/json.hpp"
#include "../Colour/Colour.h"
#include "../Positions/Positions.h"
#include <qobject.h>
#include <QColor>
// - DEFINES - //
#define SVG_EMPTY                   "Empty"
#define SVG_PERMAWALL               "PermaWall"
#define SVG_WALL                    "Wall"
#define SVG_PLAYERSPAWN             "PlayerMale"
#define SVG_SMOKE                   "Smoke"
#define SVG_SMOKE1                  "Smoke"
#define SVG_SMOKE2                  "Smoke"
#define SVG_SMOKE3                  "Smoke"
#define SVG_SMOKE4                  "Smoke"
#define SVG_SMOKE5                  "Smoke"
#define SVG_POWER_HEART             "PowerLife"
#define SVG_POWER_DMG               "PowerDmg"
#define SVG_POWER_MOREBOMB          "PowerBomb"
#define SVG_POWER_REACH             "PowerReach"
#define SVG_POWER_SPEED             "PowerSpeed"
#define SVG_PLAYER1                 "PlayerMale"
#define SVG_PLAYER2                 "PlayerFemale"
#define SVG_PLAYER3                 "PlayerMale"
#define SVG_PLAYER4                 "PlayerMale"
#define SVG_POWER_BOMB_OF_WALLS     "Cone"
#define SVG_POWER_DEPLOYABLE_WALL   "PowerWall"
#define SVG_BOMB                    "Bomb"

//////////////////////////////////////////////////////// - TILES

/**
 * @brief 
 * # JSON STRUCTURE
 * @brief
 * {
 *      "name" : "mapName",
 *      "sizeX" : number,
 *      "sizeY" : number,
 *      "amountOfPlayers" : numberOfHowManyPlayersSpawnThereIs,
 *      "map" : {
 *          {0,0,0,0,0,0,0,0,0,0,0,0},
 *          {0,0,0,0,0,0,0,0,0,0,0,0},
 *          {0,0,0,0,0,0,0,0,0,0,0,0},
 *          ...
 *          {0,0,0,0,0,0,0,0,0,0,0,0},
 *      }
 * }
 */

#pragma region old Binary struct
///**
// * @brief
// * # BinaryTilesAttributes
// * @brief
// * Struct which holds potential binary attributes for each tiles.
// * Tiles are a series of 12 bits which holds data as followed:
// * "0000 0000 0000" First 4 bits describes the tile's attributes.
// * second set of 4 bits defines the type of the object currently
// * on it. Third set of 4 bits gives the ID, or value of something
// * that is currently on that tile.
// * @brief
// * ## BIT VALUES FOR A TILE'S ATTRIBUTES
// * @brief
// * - Bit 0: Undestructible or not. 0 = Destructible
// * @brief
// * - Bit 1: Can have an object on it
// * @brief
// * - Bit 2: Can be exploded by bomb (reached by smoke particles)
// * @brief
// * - Bit 3: Is a player's potential spawn
// */
//struct BinaryTilesAttributes
//{
//    unsigned int CantBeDestroyed = 0b0000000000000001;
//    unsigned int CanHoldObjects  = 0b0000000000000010;
//    unsigned int CanBeExploded   = 0b0000000000000100;
//    unsigned int CanSpawnPlayers = 0b0000000000001000;
//};
//
///**
// * @brief
// * # BinaryTilesHoldings
// * @brief
// * Struct which holds the potential values that a tile can
// * get when it holds a certain type of thing.
// * Tiles are a series of 12 bits which holds data as followed:
// * "0000 0000 0000" First 4 bits describes the tile's attributes.
// * second set of 4 bits defines the type of the object currently
// * on it. Third set of 4 bits gives the ID, or value of something
// * that is currently on that tile.
// * @brief
// * ## BIT VALUES FOR A TILE'S ATTRIBUTES
// * @brief
// * - Bit 4: Has a destructible obstacle on it or not.
// * @brief
// * - Bit 5: Has a powerup on it or not.
// * @brief
// * - Bit 6: Has a player on it or not.
// * @brief
// * - Bit 7: Has a smoke on it or not.
// */
//struct BinaryTilesHoldings
//{
//    unsigned int HoldsDestructibleObject = 0b0000000000010000;
//    unsigned int HoldsPowerUp            = 0b0000000000100000;
//    unsigned int HoldsPlayer             = 0b0000000001000000;
//    unsigned int HoldsSmoke              = 0b0000000010000000;
//
//    unsigned int HoldsPlayerOnPowerUp           = 0b0000000001100000;
//    unsigned int HoldsPlayerOnSmoke             = 0b0000000011000000;
//    unsigned int HoldsPlayerOnSmokeOnPowerUp    = 0b0000000011100000;
//    unsigned int HoldsSmokeOnBox                = 0b0000000010010000;
//};
//
///**
// * @brief
// * # BinaryTileMasks
// * @brief
// * Used to perform masks operations on tiles such as
// * extract ID, attributes, or whats on it.
// */
//struct BinaryTileMasks
//{
//    unsigned int OnlyKeepAttributes = 0b0000000000001111;
//    unsigned int OnlyKeepHoldings   = 0b0000000011110000;
//    unsigned int OnlyKeepID         = 0b0000111100000000;
//    unsigned int OnlyKeepRESERVED   = 0b1111000000000000;
//};
//
///**
// * @brief
// * # BinaryTilesID
// * @brief
// * Struct which holds the potential values that a specific thing
// * on a tile can be. This allows a tile to know the ID of the
// * specific thing that is on it.
// * Tiles are a series of 12 bits which holds data as followed:
// * "0000 0000 0000" First 4 bits describes the tile's attributes.
// * second set of 4 bits defines the type of the object currently
// * on it. Third set of 4 bits gives the ID, or value of something
// * that is currently on that tile.
// * While there can be multiple things on a tile, this is ONLY
// * true DURING the game and only for 1 frame at best. The game
// * will handle it so only 1 thing is left on a tile. (object)
// * @brief
// * ## BIT VALUES FOR A TILE'S ATTRIBUTES
// * @brief
// * Represents a 4 bit numbers leading up to an ID to tell more
// * precisely, exactly, whats on the tile. Smoke dont hold
// * its own ID number because multiple things can be on it, and it
// * doesnt really need to be saved in the game.
// * Objects hold their own ID number so that they can be stored in
// * a @ref Map template.
// * @brief
// * ## To resume:
// * @brief
// * - If a player is on a tile, the ID of the tile = Player number.
// * @brief
// * - If a power up is on a tile, ID = PowerUp ID
// * @brief
// * - If a bomb is on a tile, ID = Bomb explosivity
// * @brief
// * - If a destructible box is on a tile, ID = health points.
// */
//struct BinaryTilesID
//{
//    unsigned int EMPTY = 0;
//};
//
///**
// * @brief
// * # BinaryDefaultTiles
// * @brief
// * Struct which holds basic default example of some tiles without
// * specific data on them.
// * @brief
// * "0000 0000 0000" First 4 bits describes the tile's attributes.
// * second set of 4 bits defines the type of the object currently
// * on it. Third set of 4 bits gives the ID, or value of something
// * that is currently on that tile.
// * @brief
// * - Bit 0: Undestructible Or not. 0 = Destructible
// * @brief
// * - Bit 1: Can have an object on it
// * @brief
// * - Bit 2: Can be exploded by bomb (reached by smoke particles)
// * @brief
// * - Bit 3: Is a player's potential spawn
// * @brief
// * - Bit 4: Has a destructible obstacle on it or not.
// * @brief
// * - Bit 5: Has a powerup on it or not.
// * @brief
// * - Bit 6: Has a player on it or not.
// * @brief
// * - Bit 7: Has a smoke on it or not.
// * @brief
// * - Bit 8 to 11: Value associated with the thing on the tile based on bits 4 to 7. 
// */
//struct BinaryDefaultTiles
//{
//    unsigned int DefaultEmptySpace                         = 0b0000000000000110; // 0x600
//    unsigned int DefaultEmptySpaceWithPotentialPlayerSpawn = 0b0000000000001110;
//    unsigned int DefaultTileWithBoxOnIt                    = 0b0000000000010110;
//    unsigned int IndestructibleWall                        = 0b0000000000000001;
//};
#pragma endregion

//////////////////////////////////////////////////////// - MAP
/**
 * @brief 
 * The map class allows a game to handle a 2
 * dimmensionnal map. The map consists of a
 * 2 dimmensionnal array filled with numbers.
 * The numbers correspond to what is there on
 * the map. 
 * The Map renders these when @ref Draw is called.
 * It is also worth mentionning that for each
 * slot in the map, 3 ASCII characters are drawn
 * to represent it.
 * The goal of this class is to draw a map in the terminal
 * or the QT application.
 */

enum class TileTypes
{
    EMPTY,
    PERMAWALL,
    WALL,
    PLAYERSPAWN,
    SMOKE,
    SMOKE1,
    SMOKE2,
    SMOKE3,
    SMOKE4,
    SMOKE5,
    POWER_HEART,
    POWER_REACH,
    POWER_SPEED,
    POWER_MOREBOMB,
    POWER_DMG,
    PLAYER1,
    PLAYER2,
    PLAYER3,
    PLAYER4,
    BOMB,
    POWER_DEPLOYABLE_WALL,
    POWER_BOMB_OF_WALLS
};

std::string GetSvg(std::string name);

class Map : public QObject
{
    Q_OBJECT
    private:
        /// @brief How big the map is horizontally.
        int sizeX = 0;
        /// @brief How big the map is vertically.
        int sizeY = 0;
        /// @brief The actual map. IS DESTROYED WHEN LOADED AND RE-CREATED.
        TileTypes map[30][30] = {};
        TileTypes changes[30][30] = {};
        /// @brief Reprensent the map as a string so it can be saved in a file.
        std::string mapAsString = "";
        /// @brief The map's name. Defaults to UNTITLED
        std::string mapName = "UNTITLED";
        /// @brief The number of player spawns. Defaults to 0
        int amountOfPlayer = 0;
        /// @brief Simply stores the map data that was used to create the map / loaded into the map. Used by @ref GetCurrentMap
        nlohmann::json storedMapData;
        std::string special = " ";
       

    public:              
        int GetSizeX();
        int GetSizeY();
        int GetAmountOfPlayer();
        std::string GetName();
        std::map<TileTypes, std::string> tileChar =
        {
            { TileTypes::EMPTY, " . "},
            { TileTypes::PERMAWALL, "   "},
            { TileTypes::WALL, "###"},
            { TileTypes::PLAYERSPAWN, " @ "},
            { TileTypes::SMOKE, "&%&"},
            { TileTypes::SMOKE1, "&%&"},
            { TileTypes::SMOKE2, "&%&"},
            { TileTypes::SMOKE3, "&%&"},
            { TileTypes::SMOKE4, "&%&"},
            { TileTypes::SMOKE5, "&%&"},
            { TileTypes::POWER_HEART, special + STRING_HEARTH + " "}, // done
            { TileTypes::POWER_DMG, special + STRING_SPADE + " "}, // done
            { TileTypes::POWER_MOREBOMB, " + "}, //done
            { TileTypes::POWER_REACH, "<->"}, //done
            { TileTypes::POWER_SPEED, ">>>"},
            { TileTypes::PLAYER1, " @ "},
            { TileTypes::PLAYER2, " @ "},
            { TileTypes::PLAYER3, " @ "},
            { TileTypes::PLAYER4, "GOD"},
            { TileTypes::POWER_BOMB_OF_WALLS, "#\x05#"},
            { TileTypes::POWER_DEPLOYABLE_WALL, ">#<"},
            { TileTypes::BOMB, special + STRING_CLUB + " "},
        };

        std::map<TileTypes, std::string> tileSvg =
        {
            { TileTypes::EMPTY,                "Empty"},
            { TileTypes::PERMAWALL,            "PermaWall"},
            { TileTypes::WALL,                 "Wall"},
            { TileTypes::PLAYERSPAWN,          "PlayerMale"},
            { TileTypes::SMOKE,                "Smoke"},
            { TileTypes::SMOKE1,               "Smoke"},
            { TileTypes::SMOKE2,               "Smoke"},
            { TileTypes::SMOKE3,               "Smoke"},
            { TileTypes::SMOKE4,               "Smoke"},
            { TileTypes::SMOKE5,               "Smoke"},
            { TileTypes::POWER_HEART,          "PowerLife"},
            { TileTypes::POWER_DMG,            "PowerDmg"}, 
            { TileTypes::POWER_MOREBOMB,       "PowerBomb"},
            { TileTypes::POWER_REACH,          "PowerReach"}, 
            { TileTypes::POWER_SPEED,          "PowerSpeed"},
            { TileTypes::PLAYER1,              "PlayerMale"},
            { TileTypes::PLAYER2,              "PlayerFemale"},
            { TileTypes::PLAYER3,              "PlayerCat"},
            { TileTypes::PLAYER4,              "PlayerMale"},
            { TileTypes::POWER_BOMB_OF_WALLS,  "Cone"},
            { TileTypes::POWER_DEPLOYABLE_WALL,"PowerWall"},
            { TileTypes::BOMB,                 "Bomb"},
        };

        std::map<TileTypes, QColor> tileColor =
        {
            { TileTypes::EMPTY,                QColor(0,0,0)},
            { TileTypes::PERMAWALL,            QColor(0,0,0)},
            { TileTypes::WALL,                 QColor(199, 122, 34)},
            { TileTypes::PLAYERSPAWN,          QColor(255,0,0)},
            { TileTypes::SMOKE,                QColor(0,0,0)},
            { TileTypes::SMOKE1,               QColor(128,0,0)},
            { TileTypes::SMOKE2,               QColor(255, 0, 0)},
            { TileTypes::SMOKE3,               QColor(128, 255, 0)},
            { TileTypes::SMOKE4,               QColor(255, 255, 0)},
            { TileTypes::SMOKE5,               QColor(128,0,255)},
            { TileTypes::POWER_HEART,          QColor(75, 240, 10)},
            { TileTypes::POWER_DMG,            QColor(75, 240, 10)},
            { TileTypes::POWER_MOREBOMB,       QColor(75, 240, 10)},
            { TileTypes::POWER_REACH,          QColor(75, 240, 10)},
            { TileTypes::POWER_SPEED,          QColor(75, 240, 10)},
            { TileTypes::PLAYER1,              QColor(255,0,0)},
            { TileTypes::PLAYER2,              QColor(21, 99, 214)},
            { TileTypes::PLAYER3,              QColor(240, 233, 29)},
            { TileTypes::PLAYER4,              QColor(11, 125, 40)},
            { TileTypes::POWER_BOMB_OF_WALLS,  QColor(75, 240, 10)},
            { TileTypes::POWER_DEPLOYABLE_WALL,QColor(75, 240, 10)},
            { TileTypes::BOMB,                 QColor(64, 64, 64)},
        };

        /**
         * @brief Construct a new Map object.
         * Builds a new map. You MUST load a
         * map through @ref LoadSavedMap
         * otherwise the map IS NOT USABLE AS IS.
         */
        Map(nlohmann::json MapData);

        /**
         * @brief 
         * Handles the various updating that
         * the map needs to do to store new data
         * as stuff inside of it.
         * @attention
         * You could perhaps do 2 buffers, compare between
         * the 2, and only redraw the map if a change is
         * seen between the current array and the old one
         * But that isn't really necessary.
         * @return true:
         * Successfully updated the map.
         * @return false:
         * Failed to update the map.
         */
        bool Update();

        /**
         * @brief 
         * Actually draws the ASCII or the sprites
         * of the map on the screen.
         * @return true:
         * Successfully drawn the map
         * @return false:
         * Failed to draw the map on the screen.
         */
        bool Draw();

        /**
         * @brief
         * Used to tell you what is at a specific
         * location on the map. Please refer to
         * the enum to know what the returned value
         * represents.
         * @param x
         * The X coordinate where the wanted tile is located.
         * @param y
         * The Y coordinate where the wanted tile is located.w
         * @return TileType 
         */
        TileTypes GetTileDataAtPosition(int x, int y);
        TileTypes GetTileDataAtPosition(Positions pos);

        /**
         * @brief
         * Replaces a tile somewhere on the map by a new
         * tile type. Is used to tell the map that there
         * is something to draw there.
         * @param x
         * The X coordinate where the wanted tile is located.
         * @param y
         * The Y coordinate where the wanted tile is located.
         * @return true:
         * Successfully replaced the tile at that location with
         * the specified tile.
         * @return false:
         * Invalid tile type / invalid coordinates
         */
        bool SetTileDataAtPosition(int x, int y, TileTypes wantedTile);

        /**
         * @brief 
         * Loads a JSON file as a map in an array.
         * File types are stored as JSONs and their
         * structure can be found at the top of the
         * file. This just overwrites the map that
         * is currently in the object. Use this
         * in the constructor if needed.
         * @ref Map.h
         * @param mapAsJSON
         * A JSON object which holds the map's attributes
         * See the top of @ref Map.h for the standard map
         * structure.
         * @return true:
         * Successfully loaded the map.
         * @return false:
         * Failed to load the map.
         */
        bool LoadMap(nlohmann::json mapAsJSON);

        /**
         * @brief 
         * Returns the current map as a JSON object
         * so that it can be saved at a specified
         * location later or whatever.
         * @attention
         * KEEP THIS FUNCTION FOR NOW, WE'LL SEE LATER
         * IF WE HAVE TIME TO DO SHIT WITH THIS.
         * FOR NOW, JUST DONT BOTHER.
         * @return nlohmann::json
         * JSON object of the map.
         */
        nlohmann::json GetCurrentMap();

        /**
         * @brief
         * Simply gives a name to the map so that it
         * can be recognized by the game and displayed
         * somewhere.
         * @attention
         * KEEP THIS FUNCTION FOR NOW, WE'LL SEE LATER
         * IF WE HAVE TIME TO DO SHIT WITH THIS.
         * FOR NOW, JUST DONT BOTHER.
         * @param newName
         * The new name that the map must have
         * @return true:
         * Successfully changed the map's name to be
         * the new wanted name
         * @return false:
         * Invalid name.
         */
        bool SetMapName(std::string newName);

        /**
         * @brief 
         * # GetASpawnPosition
         * @brief
         * Returns the coordinate to a specified potential spawning location
         * for a @ref Player on the map. You must create 2 int variables which
         * are passed to this function as pointers. This allows the method
         * to directly update these values instead of returning a pointer.
         * 
         * --> CHANGE THIS TO FIT HOW YOU FIND SPAWNS <--
         * Spawn numbers are attributed like text is read... left to right,
         * top to bottom
         * 
         * 
         * @warning
         * If the spawn number specified is out of bounds, (not enough
         * spawns on this map for an Xth @ref Player), -1 will be stored
         * as X and Y coordinates.
         * 
         * @param spawnNumber
         * Which spawn coordinates should be returned? 0 to Xth
         * @param resultedX
         * horizontal position on the map
         * @param resultedY
         * vertical position on the map
         * @return true:
         * Successfully found that player spawn
         * @return false:
         * Failed to find that player's spawn. -1 is set as X and Y.
         */
        bool GetASpawnPosition(unsigned int spawnNumber, unsigned int* resultedX, unsigned int* resultedY);

        TileTypes GetPlayerTypeFromId(int playerId);

        void EmitChanges();

    signals:
        void TileDataChanged(int x, int y, TileTypes);
};

#include "Utils.hpp"