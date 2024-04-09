/**
 * @file PortDetector.h
 * @author LyamBRS
 * @brief 
 * Header file which contains the definitions of
 * functions used to iterate through available
 * ComPorts.
 * @version 0.1
 * @date 2024-02-14
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <SetupAPI.h>
#include <devguid.h>

// - DEFINES - //

// - FUNCTIONS - //
std::vector<std::wstring> GetAvailableComPorts();

/**
 * @brief 
 * Checks if a specified COM port is listed on
 * the PC's available ports.
 * @param comPort
 * port to check. Must follow "COMX" writing
 * to be valid, don't just put the number in
 * there.
 * @return true:
 * That COM port is currently listed.
 * @return false:
 * That COM port is not listen atm.
 */
bool IsComPortListed(std::string comPort);