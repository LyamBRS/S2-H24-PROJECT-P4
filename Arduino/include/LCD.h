/**
 * @file LCD.h
 * @author LyamBRS
 * @brief 
 * Contains the header definition for the
 * LCD class.
 * @version 0.1
 * @date 2024-02-11
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include <Arduino.h>
#include <LiquidCrystal.h>
// - DEFINES - //

// - CLASS - //

/**
 * @brief
 * this class let you use an LCD screen
 * and can help print things in screen
 */
class LCD 
{
    private:
        /// @brief The register select of the LCD
        int rs;
        /// @brief The enable pin of the LCD
        int en;
        /// @brief The data pin 4 of the LCD
        int d4;
        /// @brief The data pin 5 of the LCD
        int d5;
        /// @brief The data pin 6 of the LCD
        int d6;
        /// @brief The data pin 7 of the LCD
        int d7;

    public:
        /**
         * @brief initialize the LCD screen
         * by default the size is 2 X 16
         */
        void lcdInit();

        /**
         * @brief
         * print the message on the lcd screen at the required line.
         * @param cursorRow
         * The row at which you want to display the text
         * @param cursorLine
         * the line at which you want to display the text
         * @param display
         * the text that you want to display
         */
        void print(int cursorRow, int cursorLine, char* display);

        bool SetNewLocalMessage(char* display);
        bool SetNewPCMessage(char* display);
};
