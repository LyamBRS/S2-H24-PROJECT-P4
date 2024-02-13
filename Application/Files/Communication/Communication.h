/**
 * @file Communication.h
 * @author LyamBRS
 * @brief
 * Contains header definition of the communication class
 * which is based on libraries given by teachers and
 * uses JSON files sent to an arduino and replied back.
 * This class is generic and does not handle the arduino
 * itself.
 * @version 0.1
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */

#pragma once

// - INCLUDES - //
#include <iostream>
#include <string>
#include "../Serial/SerialPort.hpp"
#include "../JSON/json.hpp"

// - DEFINES - //
#define COMMUNICATION_MESSAGE_MAX_SIZE 1024

// - CLASS - //

/**
 * @brief 
 * Communication objects handles one serial
 * port to be used to send and receive JSON
 * files as strings.
 */
class Communication
{
    private:
        /// @brief serial port's object.
        SerialPort* serialPort;

        int baudRate = 9600;
        std::string comPort = "0";
    public:

        /**
         * @brief
         * Builds a new communication object.
         * Communication objects handles one serial
         * port to be used to send and receive JSON
         * files as strings.
         */
        Communication();

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
        bool SetBaudRate(int newBaudRate);

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
        bool SetComPort(std::string newComPort);

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
        bool Connect();

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
        bool Disconnect();

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
        bool SendToSerial(nlohmann::json j_msg);

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
        bool GetSerialMessage(std::string &msg);
};
