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
#include "../Map/Utils.hpp"
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

// - CLASS - //

class cMapMenu : public cMenu
{
    private:
        int amountOfMaps = 0;
    public:
        cMapMenu(AppHandler* currentAppHandler);
        bool HandleKeyboard(int keyBoardKey);
        bool Draw();
        bool Update();
        void setSelection(int selected);
        void SelectionNext();
        void SelectionPrevious();
        bool OnEnter();
        bool OnExit();
        bool OnMapSelect();
        Map* map;
};