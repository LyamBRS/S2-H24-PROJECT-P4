/**
 * @file resultatCouleur.h
 * @author COUS1912, GRAF2102
 * @brief
 * Permet de print un résultat en couleur sur
 * Linux et sur Windows
 * @version 0.1
 * @date 2024-01-10
 * @copyright Copyright (c) 2024
 */

#pragma once

#include <iostream>

enum colors {
    black = 0,
    electric = 1,
    leaf = 2,
    lightblue = 3,
    red = 4,
    darkpurple = 5,
    gold = 6,
    lightgrey = 7,
    grey = 8,
    blue = 9,
    green = 10,
    aqua = 11,
    lightred = 12,
    purple = 13,
    yellow = 14,
    white = 15,
};

void PrintInColour(std::ostream & os, std::string toBePrinted, int foregroundColour, int backgroundColour);

void SetTerminalCursorPosition(int row, int column);

/**
 * @brief 
 * # ConsecutiveChar
 * @brief
 * Allows you to spam a character for X amount of times on your terminal.
 * This allows waaaay easier prints of decors.
 * @param os 
 * @param characterToDraw 
 * @param foregroundColour 
 * @param backgroundColour 
 * @param howMuchToRepeat 
 * @param lineEnd 
 */
void ConsecutiveChar(std::ostream & os, char characterToDraw, int foregroundColour, int backgroundColour, int howMuchToRepeat, bool lineEnd);

std::string ExePath();