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

void PrintInColour(std::ostream & os, std::string toBePrinted, char colour);

std::string ExePath();