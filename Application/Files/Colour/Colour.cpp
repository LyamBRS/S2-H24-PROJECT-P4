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

#include <codecvt>
#include "Colour.h"
#include "Windows.h"

std::string ExePath() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    std::wstring result = std::wstring(buffer).substr(0, pos);
    
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    std::string resultString =  conv.to_bytes(result);
    return resultString;
}

void SetTerminalCursorPosition(int row, int column)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {row, column};
    SetConsoleCursorPosition(hConsole, pos);
    return;
}

void ResizeTerminal(int row, int column)
{
    HWND hwnd = GetConsoleWindow();
    row = (row*8) + 100;
    column = (column*16) + 100 + 8;
    RECT rect = { 100, 100, row, column };
    MoveWindow(hwnd, rect.left, rect.top, rect.right, rect.bottom, false);
}

void PrintInColour(std::ostream & os, std::string toBePrinted, int foregroundColour, int backgroundColour)
{
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   int colour = backgroundColour * 16 + foregroundColour;
   SetConsoleTextAttribute(hConsole, colour);
   os << toBePrinted;
   SetConsoleTextAttribute(hConsole, 7);
}

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
void ConsecutiveChar(std::ostream & os, char characterToDraw, int foregroundColour, int backgroundColour, int howMuchToRepeat, bool lineEnd)
{
    std::string result = "";
    for(int i=0; i<howMuchToRepeat; i++)
    {
        result += characterToDraw;
    }

    if(lineEnd)
    {
        result += '\n';
    }

    PrintInColour(os, result, foregroundColour, backgroundColour);
}
