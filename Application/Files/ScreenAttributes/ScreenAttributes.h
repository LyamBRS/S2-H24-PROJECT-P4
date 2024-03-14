/**
 * @file ScreenAttributes.h
 * @author LyamBRS
 * @brief
 * Contains header definitions for the
 * ScreenAttributes class used to give
 * ASCII attributes to objects.
 * @version 0.1
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */
#pragma once

// - INCLUDES - //
#include <iostream>
#include <stdio.h>

// - DEFINES - //

// - CLASS - //

/**
 * @brief 
 * Simple class that allows objects or other
 * components to have basic attributes that
 * allows them to be able to be drawn inside of
 * a basic command prompt. This class will later
 * get more complex as the project moves over to
 * QT. Screenattributes allow an object to have
 * a dedicated set of ASCII characters that will
 * be printed on a command prompt using a basic
 * colour.
 */
class ScreenAttributes
{
    private:
        /// @brief The screen ASCII representation that will be printed in a terminal.
        std::string ascii = "";

        /// @brief The current colour of that object.
        int colour = ' ';

    public:

        ScreenAttributes();

        /**
         * @brief Construct a new Screen Attributes object.
         * This object allows ASCII characters to represent
         * an object. It also allows those ascii characters
         * to have a colour for when they will be printed
         * in a terminal.
         * @param wantedASCII
         * Wanted ASCII representation of the object.
         * @param wantedColour
         * Wanted colour of the object. Used when drawing
         * the ASCII on a terminal or a screen.
         */
        ScreenAttributes(std::string wantedASCII, int wantedColour);

        /**
         * @brief 
         * Gets the current ASCII attribute of
         * this object.
         * @return std::string
         */
        std::string Ascii();

        /**
         * @brief 
         * Sets a new ASCII representation to
         * the object to be drawn on the screen.
         * @param newAscii
         * The new sets of characters that will
         * be used to display that object on the
         * screen.
         * @return std::string 
         */
        std::string Ascii(std::string newAscii);

        /**
         * @brief
         * Gets the colour associated with the
         * ASCII atribute of the object. Colours
         * are defined by Windows Terminals and
         * a enum of possible colours is
         * available. Avoid writing the characters
         * by hand.
         * @return char 
         */
        int Colour();

        /**
         * @brief 
         * Sets the colour associated with the
         * ASCII atribute of the object. Colours
         * are defined by Windows Terminals and
         * a enum of possible colours is
         * available. Avoid writing the characters
         * by hand.
         * @param newColour
         * The new basic colour that will be used
         * when the ASCII will be drawn on the
         * screen.
         * @return char 
         */
        int Colour(int newColour);
};