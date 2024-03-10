/**
 * @file MapMenu.h
 * @author LyamBRS
 * @brief
 * Header definition of the MapMenu class
 * which allows a MapMenu to be handled.
 * @version 0.1
 * @date 2024-02-15
 * @copyright Copyright (c) 2024
 */
#pragma once

// - INCLUDES - //
#include "../Application/AppHandler.h"
#include "../Colour/Colour.h"
#include "../Map/Map.h"
#include "../JSON/json.hpp"
#include "Menu.h"
#include <vector>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>

// - DEFINES - //

// - FUNCTIONS - //
std::vector<nlohmann::json> GetAllMaps();
bool VerifyMap(std::string path);
nlohmann::json GetMapJson(std::string path);

// - CLASS - //

class MapMenu : public Menu
{
    private:
        int amountOfMaps = 0;
    public:
        MapMenu(AppHandler* currentAppHandler);
        bool HandleKeyboard(int keyBoardKey);
        bool Draw();
        bool Update();
        bool OnEnter();
        bool OnExit();
        bool OnMapSelect();
        Map* map;
};