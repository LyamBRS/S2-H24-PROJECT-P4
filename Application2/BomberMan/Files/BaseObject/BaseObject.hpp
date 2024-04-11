/**
 * @file BaseObject.hpp
 * @author LyamBRS
 * @brief 
 * HEader file containing the definition
 * of the abstract object class used to
 * build more sophesticated objects such
 * as bombs or players.
 * @version 0.1
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */
#pragma once

// - INCLUDES - //
#include "../Positions/Positions.h"
#include "../ScreenAttributes/ScreenAttributes.h"
#include "../Movements/Movements.h"

// - DEFINES - //

// - CLASS - //

/**
 * @brief 
 * Standard abstract object class which allows
 * more sophesticated object to have position,
 * movements and screen attributes by default
 * without needing to redefine them. Also
 * allows vectors to contain generic objects
 * rather than having to battle with bunch
 * of different types of classes.
 */
class BaseObject
{
    protected:
        /// @brief The object's position attributes. Allowing it to exist at a certain coordinate on the screen.
        Positions position = Positions(0,0);
        /// @brief Corresponds to a manuallu specified old coordinate so the player can be removed from where they used to stand
        Positions OldPosition = Positions(0,0);
        /// @brief The object's movement attributes, allowing it to move some position distance through time.
        Movements movement;
        /// @brief the object's display attributes. Allowing it to have an associated colour and command prompt representation.
        ScreenAttributes displayAttributes;

    public:
        /**
         * @brief Construct a new Object object.
         * Default object constructor. Sets
         * everything to 0.
         */
        BaseObject();

        /**
         * @brief Get the Screen Attributes object.
         * Simply returns a pointer to this objects
         * screen attributes.
         * @return ScreenAttributes* 
         */
        ScreenAttributes* GetScreenAttributes();

        /**
         * @brief Get the Movement object.
         * Simply returns a pointer to this objects
         * movement attribute class.
         * @return Movements* 
         */
        Movements* GetMovement();

        /**
         * @brief Get the Position object
         * Simply returns a pointer to this objects
         * position attribute class.
         * @return Positions* 
         */
        Positions* GetPosition();

        /**
         * @brief Set the Position object
         * Returns nothing
         * position attribute class.
         * @return  
         */
        void setPosition();

        /**
         * @brief Get the old Position object
         * Simply returns a pointer to this objects
         * position attribute class.
         * Allows you to check where the player was
         * and change that.
         * @return Positions* 
         */
        Positions* GetOldPosition();
};
