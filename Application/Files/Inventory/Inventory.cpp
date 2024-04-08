/**
 * @file Inventory.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-19
 * @copyright Copyright (c) 2024
 */

// - INCLUDES - //
#include "Inventory.h"

// - PROGRAM - //

/**
 * @brief 
 * # Inventory
 * @brief
 * Construct a new Inventory object.
 * Allows a @ref Player to have a simple Inventory in which they can
 * store a set amount of @ref PowerUps to use or get rid of at all
 * times. This inventory allows scrolling through and selecting
 * its various @ref PowerUps for the user to manage as they see fit.
 * @param amountOfSpace
 * How many slots should the inventory have?
 */
Inventory::Inventory(int amountOfSpace)
{
    maxSelection = amountOfSpace;
    selection = 0;

    // Fill inventory will nil PowerUps
    for(int i=0; i<maxSelection; i++)
    {
        inventory.push_back(PowerUp(PowerUpID::nil, 0));
    }
}

/**
 * @brief 
 * Returns a number from ranging from 0 to the inventory's max
 * slot count, which is specified in the constructor of the
 * inventory. The number never reaches the maximum because arrays
 * starts at 0. 0 being the first slot selected.
 * @return int 
 */
int Inventory::CurrentIndex()
{
    return selection;
}

/**
 * @brief 
 * Go to the previous slot in the inventory. This
 * decreases the selected slot index. Allows the 
 * user to select a powerup in their inventories.
 * @return true:
 * Successfully scrolled to the previous slot.
 * @return false:
 * Failed to go to the previous slot.
 */
bool Inventory::SelectPrevious()
{
    selection--;
    if(selection <= 0) selection = 0;
    return true;
}

/**
 * @brief 
 * Go to the next slot in the inventory. This
 * increments the selected slot index. Allows 
 * the user to select a powerup in their
 * inventories.
 * @return true:
 * Successfully scrolled to the next slot.
 * @return false:
 * Failed to go to the next slot.
 */
bool Inventory::SelectNext()
{
    selection++;
    if(selection >= (maxSelection-1)) selection = (maxSelection-1);
    return true;
}

/**
 * @brief 
 * Quickly tells you if the selected slot contains a usable
 * @ref PowerUp to use since the inventory is filled with
 * nil powerups when created.
 * @return true:
 * A valid powerup is available at the selected slot.
 * @return false:
 * No valid powerup is available at the selected slot.
 */
bool Inventory::SelectedIsUsable()
{
    int ID = inventory[selection].getType();
    return (ID != PowerUpID::nil);
}

/**
 * @brief 
 * Returns a copy of the selected @ref PowerUp while the
 * real one stored inside of the inventory is discarded
 * and deleted from the @ref Player's inventory.
 * @return PowerUp
 */
PowerUp Inventory::DiscardSelected()
{
    PowerUp selected = inventory[selection];
    inventory[selection] = PowerUp(PowerUpID::nil, 0); // Reset that slot to be the default one.
    return selected;
}

/**
 * @brief 
 * Returns a copy of the selected @ref PowerUp while the
 * real one stored inside of the inventory is used. Depending
 * on the @ref PowerUp, it will either be deleted from the
 * Inventory, or its available uses will go down 1.
 * @return PowerUp 
 */
PowerUp Inventory::UseSelected()
{
    inventory[selection].Use(); // Decreases how many times we can use it.
    PowerUp selected = inventory[selection];

    // Check if there is uses left
    if(selected.IsDrained())
    {
        DiscardSelected();
    }

    return selected;
}

/**
 * @brief
 * Returns a reference to the selected @ref PowerUp allowing
 * the @ref BomberManGame to perform various actions and drawings based
 * off the values stored in the @ref PowerUp without actually
 * using or affecting it in any ways at all.
 * @attention
 * Returns a nullptr if there is no selected @ref PowerUp
 * @return PowerUp*
 */
PowerUp* Inventory::GetSelected()
{
    return &inventory[selection];
}

/**
 * @brief 
 * Gets a reference to a specific PowerUp at a specific index
 * allowing the @ref BomberManGame to perform various actions and drawings 
 * based off the values stored in the @ref PowerUp without actually
 * using or affecting it in any ways at all.
 * @attention
 * nullptr is return if the specified index is not valid.
 * @param index
 * slot index at which to get the @ref PowerUp
 * @return PowerUp* 
 */
PowerUp* Inventory::Get(int index)
{
    if(index < 0) return nullptr;
    if(index > (maxSelection-1)) return nullptr;

    return &inventory[index];
}

/**
 * @brief 
 * Add a specific @ref PowerUp in the inventory at the first available
 * slot. Use the return statement to check if the PowerUp was successfully
 * added inside of the player's inventory or not. If it wasnt added to the
 * inventory, the PowerUp MUST remain on the @ref Map until that @ref Player
 * inventory is no longer full.
 * @param newPowerUp 
 * @return true:
 * Successfully added the powerup.
 * @return false:
 * Failed to add the powerup.
 */
bool Inventory::Add(PowerUp newPowerUp)
{
    if(IsFull()) return false;

    // Find the first available slot
    for(int i=0; i<maxSelection; i++)
    {
        if(inventory[i].getType() == PowerUpID::nil)
        {
            inventory[i] = newPowerUp;
            return true;
        }
    }
    return false;
}

/**
 * @brief 
 * Quickly tells you if the @ref PLayer's inventory is full or not.
 * @return true:
 * Its full
 * @return false:
 * There is still slots left for storage. 
 */
bool Inventory::IsFull()
{
    for(int i=0; i<maxSelection; i++)
    {
        if(inventory[i].getType() == PowerUpID::nil)
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief 
 * Tells you how many slots are left for powerups in that player's inventory.
 * You can also use @ref IsFull for better readability.
 * @return int 
 */
int Inventory::SlotsLeft()
{
    int slotsLeft = 0;
    for(int i=0; i<maxSelection; i++)
    {
        if(inventory[i].getType() == PowerUpID::nil)
        {
            slotsLeft++;
        }
    }
    return slotsLeft;
}