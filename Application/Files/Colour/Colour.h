/**
 * @file resultatCouleur.h
 * @author COUS1912, GRAF2102
 * @brief
 * Permet de print un résultat en couleur sur
 * Windows
 * @version 0.1
 * @date 2024-01-10
 * @copyright Copyright (c) 2024
 */

#pragma once

#include <iostream>

// - DEFINES - //

#define CHAR_HEARTH                         '\x03'
#define CHAR_DIAMONDS                       '\x04'
#define CHAR_CLUB                           '\x05'
#define CHAR_SPADE                          '\x06'
#define CHAR_MALE                           '\x0B'
#define CHAR_FEMALE                         '\x0C'
#define CHAR_MUSIC                          '\x0E'
#define CHAR_SPIKE_BALL                     '\x0F'
#define CHAR_RIGHT_TRIANGLE                 '\x10'
#define CHAR_LEFT_TRIANGLE                  '\x11'
#define CHAR_UP_TRIANGLE                    '\x1E'
#define CHAR_DOWN_TRIANGLE                  '\x1F'
#define CHAR_BORDER_VERTICAL                '\xBA'
#define CHAR_BORDER_HORIZONTAL              '\xCD'
#define CHAR_BORDER_CROSS                   '\xEE'
#define CHAR_BORDER_TR_CORNER               '\xBB'
#define CHAR_BORDER_TL_CORNER               '\xC9'
#define CHAR_BORDER_BR_CORNER               '\xBC'
#define CHAR_BORDER_BL_CORNER               '\xC8'
#define CHAR_CONTRAST_LOW                   '\xB0'
#define CHAR_CONTRAST_MED                   '\xB1'
#define CHAR_CONTRAST_HIGH                  '\xB2'
#define CHAR_BORDER_R_JUNCTION              '\xCC'
#define CHAR_BORDER_L_JUNCTION              '\xB9'
#define CHAR_BORDER_T_JUNCTION              '\xCA'
#define CHAR_BORDER_B_JUNCTION              '\xCB'

#define STRING_BORDER_R_JUNCTION              "\xCC"
#define STRING_BORDER_L_JUNCTION              "\xB9"
#define STRING_BORDER_T_JUNCTION              "\xCA"
#define STRING_BORDER_B_JUNCTION              "\xCB"
#define STRING_HEARTH                         "\x03"
#define STRING_DIAMONDS                       "\x04"
#define STRING_CLUB                           "\x05"
#define STRING_SPADE                          "\x06"
#define STRING_MALE                           "\x0B"
#define STRING_FEMALE                         "\x0C"
#define STRING_MUSIC                          "\x0E"
#define STRING_SPIKE_BALL                     "\x0F"
#define STRING_RIGHT_TRIANGLE                 "\x10"
#define STRING_LEFT_TRIANGLE                  "\x11"
#define STRING_UP_TRIANGLE                    "\x1E"
#define STRING_DOWN_TRIANGLE                  "\x1F"
#define STRING_BORDER_VERTICAL                "\xBA"
#define STRING_BORDER_HORIZONTAL              "\xCD"
#define STRING_BORDER_CROSS                   "\xEE"
#define STRING_BORDER_TR_CORNER               "\xBB"
#define STRING_BORDER_TL_CORNER               "\xC9"
#define STRING_BORDER_BR_CORNER               "\xBC"
#define STRING_BORDER_BL_CORNER               "\xC8"
#define STRING_CONTRAST_LOW                   "\xB0"
#define STRING_CONTRAST_MED                   "\xB1"
#define STRING_CONTRAST_HIGH                  "\xB2"

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