/**
 * @file Communication.cpp
 * @author LyamBRS
 * @brief 
 * @version 0.1
 * @date 2024-02-13 
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include "Communication.h"

/**
 * @brief
 * Builds a new communication object.
 * Communication objects handles one serial
 * port to be used to send and receive JSON
 * files as strings.
 */
Communication::Communication()
{
    serialPort = new SerialPort(comPort.c_str(), baudRate);
}

/**
 * @brief
 * Sets the baud rate at which the serial
 * port object will attempt to communicate
 * with. The serial port must be closed
 * before you can successfully changed the
 * COM port value.
 * @param newBaudRate
 * The new Baudrate to use for the COM port 
 * @return true:
 * Successfully set a new baud rate for the
 * communication port.
 * @return false 
 * Invalid BAUD rate value / serial port already opened.
 */
bool Communication::SetBaudRate(int newBaudRate)
{
    if(serialPort->isConnected()) return false;
    baudRate = newBaudRate;
    return true;
}

/**
 * @brief
 * Sets a new COM port to be used by
 * this serial port. The serial port
 * must be closed before you can
 * successfully changed the COM port
 * value.
 * @param newComPort
 * Value of the port to use.
 * @return true:
 * Successfully set the COM port to
 * a new value
 * @return false:
 * Invalid value / port already opened 
 */
bool Communication::SetComPort(std::string newComPort)
{
    if(serialPort->isConnected()) return false;
    comPort = newComPort;
    return true;
}

/**
 * @brief
 * Returns the baud rate currently configured in the
 * Communication handler. See @ref SetBaudRate for
 * more detailed information about baudrates.
 * @return int 
 */
int Communication::GetBaudRate()
{
    return baudRate;
}

/**
 * @brief
 * Returns the com port that is currently configured
 * in the Communication handler. See @ref SetComPort
 * for more detailed information about Com ports.
 * @return std::string 
 */
std::string Communication::GetComPort()
{
    return comPort;
}

/**
 * @brief 
 * Attempts to use the specified COM
 * port and the specified baud rate
 * to open a communication with a
 * specified serial port.
 * @return true:
 * Successfully opened the serial port
 * for communications
 * @return false:
 * Failed to open the serial port for
 * communications.
 */
bool Communication::Connect()
{
    if(connectCalled)
    {
        return false;
    }

    if(serialPort->isConnected()) return false;

    serialPort = new SerialPort(comPort.c_str(), baudRate);
    connectCalled = true;
    if(!serialPort->isConnected()) return false;
    return true;
}

/**
 * @brief 
 * Disconnects the serial port. Releases
 * it so that it can be used for other
 * things.
 * @attention
 * # CALL BEFORE DELETING THIS OBJECT
 * @return true:
 * Successfully disconnected the port
 * @return false:
 * Failed to disconnect the port. Oh oh.
 */
bool Communication::Disconnect()
{
    if(!serialPort->isConnected()) return false;
    serialPort->closeSerial();
    serialPort->~SerialPort();
    connectCalled = false;
    return true;
}

/**
 * @brief 
 * Sends a JSON file on a serial port to
 * a target com port. You must build the
 * JSON on your end before sending it.
 * @param j_msg
 * JSON file to send on the serial port
 * @return true:
 * Successfully sent the JSON on the port.
 * @return false:
 * Port not opened / error while sending.
 */
bool Communication::SendToSerial(nlohmann::json j_msg)
{
    if(!serialPort->isConnected()) return false;

    // CODE FROM LIB EXAMPLE
    std::string msg = j_msg.dump();
    bool result = serialPort->writeSerialPort(msg.c_str(), msg.length());
    return result;
}

/**
 * @brief
 * Puts the current message stored in the
 * serial buffer in a string. You then need
 * to parse said string as a JSON object.
 * @param msg
 * Message inside the serial buffer.
 * @return true:
 * Successfully returned the  message in the serial
 * buffer.
 * @return false 
 */
bool Communication::GetSerialMessage(std::string &msg)
{
    if(!serialPort->isConnected()) return false;

    // Return 0 if error
    // Message output in msg
    std::string str_buffer;
    char char_buffer[COMMUNICATION_MESSAGE_MAX_SIZE];
    int buffer_size;

    msg.clear(); // clear string
    // Read serialport until '\n' character (Blocking)

    buffer_size = serialPort->readSerialPort(char_buffer, COMMUNICATION_MESSAGE_MAX_SIZE);
    str_buffer.assign(char_buffer, buffer_size);
    msg.append(str_buffer);

    return true;
}

/**
 * @brief 
 * Returns wether the SerialPort is connected
 * successfully or not.
 * @return true:
 * Is connected
 * @return false:
 * Is not connected. 
 */
bool Communication::ConnectionStatus()
{
    if(!connectCalled)
    {
        return false;
    }
    return serialPort->isConnected();
}