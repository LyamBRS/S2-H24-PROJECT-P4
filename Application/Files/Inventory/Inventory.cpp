/**
 * @file Player.cpp
 * @author
 * -
 * @author
 * - YOUR NAME
 * @version 0.1
 * @date 2024-03-12
 * @copyright Copyright (c) 2024
 */


 // - INCLUDES - //
#include "Inventory.h"

Inventory::Inventory() {

}

Inventory::~Inventory() {

}

void Inventory::addInventory(PowerUp* pouvoir) {
	vectPowerUp.push_back(pouvoir);
}


PowerUp* Inventory::getInventory() {
	return vectPowerUp;
}

void Inventory::resetInventory() {
	vectPowerUp.clear();
}