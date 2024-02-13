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

// - CLASS - //

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