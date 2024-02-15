#include "PortDetector.h"

std::vector<std::wstring> GetAvailableComPorts() //added function to find the present serial 
{
    std::vector<std::wstring> comPorts;
    wchar_t lpTargetPath[5000]; // buffer to store the path of the COMPORTS
    bool gotPort = false; // in case the port is not found

    for (int i = 0; i < 255; i++) // checking ports from COM0 to COM255
    {
        std::wstring str = L"COM" + std::to_wstring(i); // converting to COM0, COM1, COM2
        DWORD test = QueryDosDevice(str.c_str(), lpTargetPath, 5000);

        // Test the return value and error if any
        if (test != 0) //QueryDosDevice returns zero if it didn't find an object
        {
            comPorts.push_back(str);
            // std::wcout << str << ": " << lpTargetPath << std::endl;
            gotPort = true;
        }

        if (::GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
        }
    }

    return comPorts;
}

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
bool IsComPortListed(std::string comPort)
{
    std::vector<std::wstring> ports = GetAvailableComPorts();

    for(int portIndex=0; portIndex<ports.size(); portIndex++)
    {
        std::string portAsString(ports[portIndex].begin(), ports[portIndex].end());
        if(portAsString == comPort) return true;
    }
    return false;
}