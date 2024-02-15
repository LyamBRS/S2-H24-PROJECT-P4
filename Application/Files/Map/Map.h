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
// - DEFINES - //


//////////////////////////////////////////////////////// - TILES

/**
 * @brief
 * # BinaryTilesAttributes
 * @brief
 * Struct which holds potential binary attributes for each tiles.
 * Tiles are a series of 12 bits which holds data as followed:
 * "0000 0000 0000" First 4 bits describes the tile's attributes.
 * second set of 4 bits defines the type of the object currently
 * on it. Third set of 4 bits gives the ID, or value of something
 * that is currently on that tile.
 * @brief
 * ## BIT VALUES FOR A TILE'S ATTRIBUTES
 * @brief
 * - Bit 0: Undestructible or not. 0 = Destructible
 * @brief
 * - Bit 1: Can have an object on it
 * @brief
 * - Bit 2: Can be exploded by bomb (reached by smoke particles)
 * @brief
 * - Bit 3: Is a player's potential spawn
 */
struct BinaryTilesAttributes
{
    unsigned int CantBeDestroyed = 0b0000000000000001;
    unsigned int CanHoldObjects  = 0b0000000000000010;
    unsigned int CanBeExploded   = 0b0000000000000100;
    unsigned int CanSpawnPlayers = 0b0000000000001000;
};

/**
 * @brief
 * # BinaryTilesHoldings
 * @brief
 * Struct which holds the potential values that a tile can
 * get when it holds a certain type of thing.
 * Tiles are a series of 12 bits which holds data as followed:
 * "0000 0000 0000" First 4 bits describes the tile's attributes.
 * second set of 4 bits defines the type of the object currently
 * on it. Third set of 4 bits gives the ID, or value of something
 * that is currently on that tile.
 * @brief
 * ## BIT VALUES FOR A TILE'S ATTRIBUTES
 * @brief
 * - Bit 4: Has a destructible obstacle on it or not.
 * @brief
 * - Bit 5: Has a powerup on it or not.
 * @brief
 * - Bit 6: Has a player on it or not.
 * @brief
 * - Bit 7: Has a smoke on it or not.
 */
struct BinaryTilesHoldings
{
    unsigned int HoldsDestructibleObject = 0b0000000000010000;
    unsigned int HoldsPowerUp            = 0b0000000000100000;
    unsigned int HoldsPlayer             = 0b0000000001000000;
    unsigned int HoldsSmoke              = 0b0000000010000000;

    unsigned int HoldsPlayerOnPowerUp           = 0b0000000001100000;
    unsigned int HoldsPlayerOnSmoke             = 0b0000000011000000;
    unsigned int HoldsPlayerOnSmokeOnPowerUp    = 0b0000000011100000;
    unsigned int HoldsSmokeOnBox                = 0b0000000010010000;
};

/**
 * @brief
 * # BinaryTileMasks
 * @brief
 * Used to perform masks operations on tiles such as
 * extract ID, attributes, or whats on it.
 */
struct BinaryTileMasks
{
    unsigned int OnlyKeepAttributes = 0b0000000000001111;
    unsigned int OnlyKeepHoldings   = 0b0000000011110000;
    unsigned int OnlyKeepID         = 0b0000111100000000;
    unsigned int OnlyKeepRESERVED   = 0b1111000000000000;
};

/**
 * @brief
 * # BinaryTilesID
 * @brief
 * Struct which holds the potential values that a specific thing
 * on a tile can be. This allows a tile to know the ID of the
 * specific thing that is on it.
 * Tiles are a series of 12 bits which holds data as followed:
 * "0000 0000 0000" First 4 bits describes the tile's attributes.
 * second set of 4 bits defines the type of the object currently
 * on it. Third set of 4 bits gives the ID, or value of something
 * that is currently on that tile.
 * While there can be multiple things on a tile, this is ONLY
 * true DURING the game and only for 1 frame at best. The game
 * will handle it so only 1 thing is left on a tile. (object)
 * @brief
 * ## BIT VALUES FOR A TILE'S ATTRIBUTES
 * @brief
 * Represents a 4 bit numbers leading up to an ID to tell more
 * precisely, exactly, whats on the tile. Smoke dont hold
 * its own ID number because multiple things can be on it, and it
 * doesnt really need to be saved in the game.
 * Objects hold their own ID number so that they can be stored in
 * a @ref Map template.
 * @brief
 * ## To resume:
 * @brief
 * - If a player is on a tile, the ID of the tile = Player number.
 * @brief
 * - If a power up is on a tile, ID = PowerUp ID
 * @brief
 * - If a bomb is on a tile, ID = Bomb explosivity
 * @brief
 * - If a destructible box is on a tile, ID = health points.
 */
struct BinaryTilesID
{
    unsigned int EMPTY = 0;
};

/**
 * @brief
 * # BinaryDefaultTiles
 * @brief
 * Struct which holds basic default example of some tiles without
 * specific data on them.
 * @brief
 * "0000 0000 0000" First 4 bits describes the tile's attributes.
 * second set of 4 bits defines the type of the object currently
 * on it. Third set of 4 bits gives the ID, or value of something
 * that is currently on that tile.
 * @brief
 * - Bit 0: Undestructible Or not. 0 = Destructible
 * @brief
 * - Bit 1: Can have an object on it
 * @brief
 * - Bit 2: Can be exploded by bomb (reached by smoke particles)
 * @brief
 * - Bit 3: Is a player's potential spawn
 * @brief
 * - Bit 4: Has a destructible obstacle on it or not.
 * @brief
 * - Bit 5: Has a powerup on it or not.
 * @brief
 * - Bit 6: Has a player on it or not.
 * @brief
 * - Bit 7: Has a smoke on it or not.
 * @brief
 * - Bit 8 to 11: Value associated with the thing on the tile based on bits 4 to 7. 
 */
struct BinaryDefaultTiles
{
    unsigned int DefaultEmptySpace                         = 0b0000000000000110; // 0x600
    unsigned int DefaultEmptySpaceWithPotentialPlayerSpawn = 0b0000000000001110;
    unsigned int DefaultTileWithBoxOnIt                    = 0b0000000000010110;
    unsigned int IndestructibleWall                        = 0b0000000000000001;
};

//////////////////////////////////////////////////////// - MAP
/**
 * @brief 
 * The map class allows a game to handle a 2
 * dimmensionnal map. The map consists of a
 * 2 dimmensionnal array filled with numbers.
 * The numbers correspond to what is there on
 * the map. There CANNOT be multiple things at
 * the same place at the same time.
 * The Map renders these when @ref Draw is called.
 * It is also worth mentionning that for each
 * slot in the map, 3 ASCII characters are drawn
 * to represent it.
 */
class Map
{
    private:
        /// @brief How big the map is horizontally.
        int sizeX = 0;
        /// @brief How big the map is vertically.
        int sizeY = 0;
        /// @brief The actual map. IS DESTROYED WHEN LOADED AND RE-CREATED.
        int map[1][1] = {};
        /// @brief Reprensent the map as a string so it can be saved in a file.
        std::string mapAsString = "";
        /// @brief The map's name. Defaults to UNTITLED
        std::string mapName = "UNTITLED";

    public:

        /**
         * @brief Construct a new Map object.
         * Builds a new map. You MUST load a
         * map through @ref LoadSavedMap
         * otherwise the map IS NOT USABLE AS IS.
         */
        Map();

        /**
         * @brief 
         * Handles the various updating that
         * the map needs to do to store new data
         * as stuff inside of it.
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
         * The Y coordinate where the wanted tile is located.
         * @return int 
         */
        int GetTileDataAtPosition(int x, int y);

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
        bool SetTileDataAtPosition(int x, int y, int wantedTile);

        /**
         * @brief 
         * Loads a text file as a map in an array.
         * File types are stored as JSONs and their
         * structure can be found at the top of 
         * @ref Map.h
         * @param filePath
         * System path pointing to the file that
         * needs to be loaded as a map.
         * @return true:
         * Successfully loaded the map.
         * @return false:
         * Failed to load the map.
         */
        bool LoadSavedMap(std::wstring filePath);

        /**
         * @brief 
         * Saves the current map loaded in this object
         * in a JSON file somewhere on the user system.
         * This also converts the array into a string.
         * @param filePath
         * System path pointing to the file that
         * needs to be overwritten or created
         * @return true:
         * Successfully saved the map at the specified
         * emplacement.
         * @return false:
         * An error occured and the map could not
         * be saved at the specified place. 
         */
        bool SaveCurrentMap(std::wstring filePath);

        /**
         * @brief
         * Simply gives a name to the map so that it
         * can be recognized by the game and displayed
         * somewhere.
         * @param newName
         * The new name that the map must have
         * @return true:
         * Successfully changed the map's name to be
         * the new wanted name
         * @return false:
         * Invalid name.
         */
        bool SetMapName(std::string newName);
};