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

    std::string wss = "\\RESULTAT_TEST.txt";

    resultString.append(wss);

    return resultString;
}


void PrintInColour(std::ostream & os, std::string toBePrinted, int foregroundColour, int backgroundColour)
{
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   int colour = backgroundColour * 16 + foregroundColour;
   SetConsoleTextAttribute(hConsole, colour);
   os << toBePrinted;
   SetConsoleTextAttribute(hConsole, 7);
}
