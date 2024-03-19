/**
 * @file Inventory.h
 * @author LyamBRS
 * @brief
 * Used to create a simple @ref PowerUp inventory for players to hold 
 * select and use various @ref PowerUp during their gameplays
 * @version 0.1
 * @date 2024-03-19
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDE - //
#include "../PowerUp/PowerUp.h"
#include <vector>

// - DEFINES - //
#define INVENTORY_MAX_SLOT 5

// - CLASS - //

/**
 * @brief 
 * # Inventory
 * @brief
 * Allows a @ref Player to have a simple Inventory in which they can
 * store a set amount of @ref PowerUps to use or get rid of at all
 * times. This inventory allows scrolling through and selecting
 * its various @ref PowerUps for the user to manage as they see fit.
 */
class Inventory 
{
    private:
        /// @brief What is the current index? Used to scroll through the inventory
        int selection = 0;
        /// @brief What is the highest slot value reachable before we loop around?
        int maxSelection = 0;
        /// @brief The actual inventory which this class manages for us.
        std::vector<PowerUp> inventory;

    public:
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
        Inventory(int amountOfSpace);

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
        bool SelectPrevious();

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
        bool SelectNext();

        /**
         * @brief 
         * Returns a copy of the selected @ref PowerUp while the
         * real one stored inside of the inventory is discarded
         * and deleted from the @ref Player's inventory.
         * @return PowerUp
         */
        PowerUp DiscardSelected();

        /**
         * @brief 
         * Returns a copy of the selected @ref PowerUp while the
         * real one stored inside of the inventory is used. Depending
         * on the @ref PowerUp, it will either be deleted from the
         * Inventory, or its available uses will go down 1.
         * @return PowerUp 
         */
        PowerUp UseSelected();

        /**
         * @brief
         * Returns a reference to the selected @ref PowerUp allowing
         * the @ref Game to perform various actions and drawings based
         * off the values stored in the @ref PowerUp without actually
         * using or affecting it in any ways at all.
         * @attention
         * Returns a nullptr if there is no selected @ref PowerUp
         * @return PowerUp*
         */
        PowerUp* GetSelected();

        /**
         * @brief 
         * Gets a reference to a specific PowerUp at a specific index
         * allowing the @ref Game to perform various actions and drawings 
         * based off the values stored in the @ref PowerUp without actually
         * using or affecting it in any ways at all.
         * @attention
         * nullptr is return if the specified index is not valid.
         * @param index
         * slot index at which to get the @ref PowerUp
         * @return PowerUp* 
         */
        PowerUp* Get(int index);

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
        bool Add(PowerUp newPowerUp);

        /**
         * @brief 
         * Quickly tells you if the @ref PLayer's inventory is full or not.
         * @return true:
         * Its full
         * @return false:
         * There is still slots left for storage. 
         */
        bool IsFull();

        /**
         * @brief 
         * Tells you how many slots are left for powerups in that player's inventory.
         * You can also use @ref IsFull for better readability.
         * @return int 
         */
        int SlotsLeft();

        /**
         * @brief 
         * Returns a number from ranging from 0 to the inventory's max
         * slot count, which is specified in the constructor of the
         * inventory. The number never reaches the maximum because arrays
         * starts at 0. 0 being the first slot selected.
         * @return int 
         */
        int CurrentIndex();

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
        bool SelectedIsUsable();
};