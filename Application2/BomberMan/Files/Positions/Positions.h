/**
 * @file Positions.h
 * @author LyamBRS
 * @brief
 * Contains header definitions for the
 * Position class used to give
 * position attributes to objects.
 * @version 0.1
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */
#pragma once

// - INCLUDES - //

// - DEFINES - //

// - CLASS - //

/**
 * @brief 
 * Used to give a position on the map
 * to a thing. Simply gives it 2D X,Y
 * coordinates.
 */
class Positions
{
    private:
        /// @brief The current X coordinate of the object.
        int x = 0;
        /// @brief The current Y coordinate of the object.
        int y = 0;

    public:
        /**
         * @brief Construct a new Positions object.
         * Creates a new set of position for something.
         * These positions are solely 2D based.
         * You also need to specify an initial value.
         * @param initialX
         * Which X coordinate should this position
         * point to initially?
         * @param initialY
         * WHich Y coordinate should this position
         * point to initially?
         */
        Positions(int initialX, int initialY);

        /**
         * @brief 
         * Give new 2D coordinates to give a new
         * position value at the same time instead
         * of calling X and Y at different times.
         * @param newX
         * The new X coordinate of the position.
         * @param newY
         * The new Y coordinate of the position.
         * @return true:
         * Successfully defined these coordinates as
         * the new position 
         * @return false:
         * Failed to set these coordinates as the
         * new position.
         */
        bool SetNewCoordinates(int newX, int newY);

        /**
         * @brief 
         * Gets the X coordinate of the object.
         * X coordinate is the horiontal position
         * on the map, or the screen.
         * @return int 
         */
        int X();

        /**
         * @brief 
         * Sets the X coordinate of the object.
         * X coordinate is the horiontal position
         * on the map, or the screen.
         * @param newX
         * The new X coordinate of the position.
         * @return int 
         */
        int X(int newX);

        /**
         * @brief 
         * Gets the Y coordinate of the object.
         * Y coordinate is the horiontal position
         * on the map, or the screen.
         * @return int 
         */
        int Y();

        /**
         * @brief 
         * Sets the Y coordinate of the object.
         * Y coordinate is the horiontal position
         * on the map, or the screen.
         * @param newY
         * The new Y coordinate of the position.
         * @return int 
         */
        int Y(int newY);

        bool operator==(Positions comparator);
};