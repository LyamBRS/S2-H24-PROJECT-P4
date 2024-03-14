/**
 * @file Player.h
 * @author Victor Mak Anthony sauvageau François Maheux
 * @brief
 * Header file used for the player's
 * class. Player class shenanigans
 * See @ref Player for a better
 * description.
 * @version 0.1
 * @date 2024-03-14
 * @copyright Copyright (c) 2024
 */
#pragma once

 // - INCLUDES - //
#include <iostream>
#include "../BaseObject/BaseObject.hpp"
#include "../PowerUp/PowerUp.h"
#include <vector>
using namespace std;

// - DEFINES - //

// - FUNCTION - //

// - CLASS - //

class Inventory
{
public:
	Inventory();
	~Inventory();
	void addInventory();
	PowerUp* getInventory();
	void resetInventory();

private:
	vector<PowerUp*> vectPowerUp;
};